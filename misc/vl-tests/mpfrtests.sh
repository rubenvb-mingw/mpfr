#!/bin/sh

# Test of MPFR tarballs with various options.
# Written in 2011-2014 by Vincent Lefevre.
#
# Usage: ./mpfrtests.sh [ +<host> ] [ <archive.tar.*> ] < mpfrtests.data
#    or  ./mpfrtests.sh -C
#
# In normal use (first form):
#   A +<host> argument can be needed when the FQDN is not set correctly.
#   The default <archive.tar.*> value is "mpfr-tests.tar.gz".
#   A file mpfrtests.<host>.out is output.
# With the -C option (second form):
#   Clean-up: Any temporary mpfrtests directory is removed (such
#   a directory isn't removed automatically in case of abnormal
#   termination, in order to be able to debug).

# For the Solaris /bin/sh
{ a=a; : ${a%b}; } 2> /dev/null || test ! -x /usr/xpg4/bin/sh || \
  exec /usr/xpg4/bin/sh -- "$0" ${1+"$@"}

prefix="${TMPDIR:-/tmp}/mpfrtests-$USER-"

if [ "x$1" = "x-C" ]; then
  chmod -R u+w "$prefix"*
  rm -rf "$prefix"*
  exit 0
fi

set -e

# Avoid errors due to missing locales (e.g. from ICC).
export LC_ALL=C

case "$1" in
  +*) fqdn=${1#+}; shift ;;
  *)  fqdn=$(perl -MPOSIX -e 'print((gethostbyname((uname)[1]))[0])') ;;
esac
printf "Host: %s\n" "$fqdn"

pwd=$(pwd)
out=$pwd/mpfrtests.$fqdn.out
rm -f "$out"

gmprx='.*gmp.h version and libgmp version are the same... (\(.*\)\/.*'
mj="make ${MAKE_JOBS:+-j$MAKE_JOBS}"
tgz="${1:-mpfr-tests.tar.gz}"

case "$tgz" in
  *bz2) unarch=bunzip2 ;;
  *gz)  unarch=gunzip ;;
  *xz)  unarch=unxz ;;
  *) echo "Unknown file extension in $tgz" >&2; exit 1 ;;
esac

# Note: the "|| true" is for NetBSD's buggy sh.
unset tmpdir || true

# We need something that should work in all POSIX shells...
dotee()
{
  rm -f "$2.st"
  { eval "$1"; echo $? > "$2.st"; } 2>&1 | tee "$2"
  st=$(cat "$2.st" 2> /dev/null)
  [ -n "$st" ]
  rm -f "$2.st"
  [ "$st" -eq 0 ] || exit "$st"
}

tst()
{
  first=1
  while read line
  do
    printf "%s\n" "$line"
    case "$line" in
      PROC:*)
        [ -n "$first" ]
        echo "* $fqdn ($(${1:-.}/config.guess) / ${line#PROC:})" > "$out"
        [ -z "$1" ] || echo "with objdir != srcdir" >> "$out"
        version=$(cat ${1:-.}/VERSION)
        echo "MPFR version: $version" >> "$out"
        versnum=$(eval "expr $(echo $version | \
          sed -n 's/^\([0-9]\{1,\}\)\.\([0-9]\{1,\}\)\.\([0-9]\{1,\}\).*/10000 \\* \1 + 100 \\* \2 + \3/p')")
        ;;
      CHECK-BEGIN*)
        [ -z "$first" ]
        [ -z "$check" ]
        if expr $versnum ${line#CHECK-BEGIN} > /dev/null; then
          check=1
          if [ -z "$1" ]; then
            conf="./configure"
          else
            mkdir obj
            cd obj
            conf="../$1/configure"
          fi
        else
          while read line
          do
            if [ "$line" = CHECK-END ]; then break; fi
          done
        fi
        ;;
      ENV:*)
        [ -n "$check" ]
        # NOTE: The environment will be restored before the next test.
        v=${line#ENV:}
        var=${v%%=*}
        val=$(env | grep "^$var=" || true)
        if [ -z "$val" ]; then
          env="$env unset $var;"
        else
          env="$env $var=\"${val#*=}\";"
        fi
        printf "ENV: %s\n" "$v" >> "$out"
        eval "export $v"
        ;;
      EVAL:*)
        [ -z "$first" ]
        # NOTE: Do not use commands that could affect later tests unless
        # this is done on purpose, such as setting environment variables
        # (for this, use the "ENV:" feature). Use "EVAL:" to run commands
        # that affect the build, not to output information ("INFO:").
        cmd=${line#EVAL:}
        printf "\$ %s\n" "$cmd" >> "$out"
        eval $cmd
        ;;
      CONF:*)
        [ -n "$check" ]
        [ -n "$conf" ]
        # Quote each configure parameter with double quotes, thus allowing
        # expansion of environment variables (possibly set with "ENV:").
        conf="$conf \"${line#CONF:}\""
        ;;
      INFO:*)
        [ -n "$check" ]
        if [ -n "$conf" ]; then
          echo '$ ./config.status -V' >> "$out"
          echo "*** Running configure ***"
          echo "$conf"
          dotee "$conf" mpfrtests.cfgout
          ./config.status -V | sed '/with options/q' >> "$out"
          gmpvers=$(sed -n "s/$gmprx/\1/p" mpfrtests.cfgout)
          [ -n "$gmpvers" ]
          printf "[GMP %s]\n" "$gmpvers" >> "$out"
          rm mpfrtests.cfgout
          CC=$(sed -n 's/^CC *= *//p' Makefile)
          unset conf || true
        fi
        cmd=${line#INFO:}
        case "$cmd" in
          CCV:*)
            printf "CC = %s\n" "$CC" >> "$out"
            eval "$CC ${cmd#CCV:} 2>&1 | head -n 1" >> "$out"
            ;;
          *)
            printf "\$ %s\n" "${cmd% | head -n 1}" >> "$out"
            eval $cmd >> "$out"
            ;;
        esac
        ;;
      CHECK-END)
        [ -n "$check" ]
        [ -z "$conf" ]
        echo "*** Running make ***"
        eval $mj
        echo "*** Running make check ***"
        dotee "$mj check" mpfrtests.makeout
        sed -n "/: tzeta_ui/,/tests passed/ {
                  s/^.*\(MPFR tuning parameters.*\)/[\1]/p
                  s/^\(.*tests passed\)/--> \1/p
                  / PASS:/,/ FAIL:/H
                  / ERROR:/ {
                    g
                    s!.* PASS: *\([0-9]\{1,\}\).* SKIP: *\([0-9]\{1,\}\).* FAIL: *\([0-9]\{1,\}\).*!--> PASS: \1 / SKIP: \2 / FAIL: \3!p
                  }
                }" mpfrtests.makeout >> "$out"
        echo "*** Cleaning up ***"
        if [ -z "$1" ]; then
          rm mpfrtests.makeout
          make distclean
        else
          cd ..
          rm -rf obj
        fi
        [ -z "$env" ] || eval "$env"
        unset check || true
        ;;
      \#*)
        continue
        ;;
      ?*)
        echo "$0: bad data ($line)" >&2
        [ -d "$tmpdir" ] && { cd; chmod -R u+w "$tmpdir"; rm -rf "$tmpdir"; }
        exit 1
        ;;
      *)
        return 0
        ;;
    esac
    unset first || true
  done
}

tstall()
{
  printf "Tests in %s\n" "$(pwd)"
  while read line
  do
    [ "HOST:$fqdn" = "$line" ] && tst "$@"
  done
  return 0
}

mktmpdir()
{
  tmpdir="${prefix}$$"
  rm -rf "$tmpdir"
  mkdir "$tmpdir"
  chmod 700 "$tmpdir"
  [ ! -h "$tmpdir" ]
}

if [ -x configure ]; then
  # Here the temporary directory is not used by the script itself;
  # it is created in case it is used by mpfrtests.data commands.
  mktmpdir
  [ ! -f Makefile ] || make distclean
  tstall
  rm -rf "$tmpdir"
elif [ -f "$tgz" ]; then
  mktmpdir
  cd "$tmpdir"
  case "$tgz" in
    /*) ;;
    *) tgz="$pwd/$tgz" ;;
  esac
  $unarch -c "$tgz" | tar xf -
  # When $$ (the PID) is even, test MPFR with objdir != srcdir.
  case $$ in
    *[02468])
      # Make srcdir read-only to detect any attempt to modify it.
      chmod -R a-w mpfr-*
      tstall mpfr-*
      chmod -R u+w mpfr-*
      ;;
    *[13579])
      cd mpfr-*
      tstall
      ;;
    *)
      echo "$0: internal error" >&2
      exit 1
      ;;
  esac
  cd "$pwd"
  rm -rf "$tmpdir"
else
  echo "$0: can't find executable configure or .tar.gz file" >&2
  exit 1
fi

printf "OK, output in %s\n" "$out"
exit 0

# $Id: mpfrtests.sh 79823 2015-06-12 16:50:18Z vinc17/xvii $
