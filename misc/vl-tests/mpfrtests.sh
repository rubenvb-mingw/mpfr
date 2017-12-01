#!/bin/sh

# Test of MPFR tarballs with various options.
#
# Written in 2011-2017 by Vincent Lefevre <vincent@vinc17.net>.
# This script is free software; you can copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.
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
#
# Environment variables MAKE (default: "make") and MAKE_JOBS (an integer)
# can be provided either via mpfrtests.data (preferred for MAKE) or via
# the command line (preferred for MAKE_JOBS).

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

# Additional tests.
# Test MPFR_FOO can be disabled for a particular "make check"
# with "ENV:MPFR_FOO" (which unsets MPFR_FOO for this run).
export MPFR_CHECK_LIBC_PRINTF=1
export MPFR_CHECK_MAX=1
export MPFR_SUSPICIOUS_OVERFLOW=1

case "$1" in
  +*) fqdn=${1#+}; shift ;;
  *)  fqdn=$(perl -MPOSIX -e 'print((gethostbyname((uname)[1]))[0])') ;;
esac
printf "Host: %s\n" "$fqdn"

pwd=$(pwd)
out=$pwd/mpfrtests.$fqdn.out
rm -f "$out"

dd="------------------------------------------------------------------------"
ed="========================================================================"
gmprx='.*gmp.h version and libgmp version are the same... '
mj='${MAKE:-make} ${MAKE_JOBS:+-j$MAKE_JOBS}'
tgz="${1:-mpfr-tests.tar.gz}"
cr="$(printf \\r)"

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

lineout()
{
  printf "%s %s (%d) $dd\n" "---" "$fqdn" $ntests | cut -b -56 >> "$out"
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
        uname -a >> "$out"
        unset os || true
        if [ -f /etc/os-release ]; then
          os1=$(. /etc/os-release; echo "$PRETTY_NAME")
        elif [ -f /etc/release ]; then
          os1=$(head -n 1 /etc/release)
        fi
        # http://stackoverflow.com/a/3352015/3782797
        os2="${os1#"${os1%%[![:space:]]*}"}"
        os3="${os2%"${os2##*[![:space:]]}"}"
        [ -z "$os3" ] || printf "OS: %s\n" "$os3" >> "$out"
        version=$(cat ${1:-.}/VERSION)
        echo "MPFR version: $version${svnvers:+ [$svnvers]}" >> "$out"
        versnum=$(eval "expr $(echo $version | \
          sed -n 's/^\([0-9]\{1,\}\)\.\([0-9]\{1,\}\)\.\([0-9]\{1,\}\).*/10000 \\* \1 + 100 \\* \2 + \3/p')")
        ;;
      CHECK-BEGIN*)
        [ -z "$first" ]
        [ -z "$check" ]
        if expr $versnum ${line#CHECK-BEGIN} > /dev/null; then
          check=1
          lineout
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
        env=""
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
          env="$env export $var=\"${val#*=}\";"
        fi
        printf "ENV: %s\n" "$v" >> "$out"
        # Unset the variable for the case "ENV:VAR"; this is different
        # from setting it to null. Since the variable may reference to
        # itself, it would be incorrect to do an unconditional "unset"
        # followed by the "export" (for the PATH variable, this would
        # also be incorrect).
        if [ "$v" = "$var" ]; then
          eval "unset $var || true"
        else
          eval "export $v"
        fi
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
          grep '^mpfr_cv_' config.log >> "$out"
          gmpv1=$(sed -n "s/$gmprx//p" mpfrtests.cfgout)
          if [ -z "$gmpv1" ]; then
            echo "$0: can't get GMP version" >&2
            exit 1
          elif [ "x$gmpv1" != "xcannot test" ]; then
            gmpvers=$(printf "%s\n" "$gmpv1" | \
                      sed -n "s/^(\(.*\)\/.*) yes/\1/p")
            if [ -z "$gmpvers" ]; then
              echo "$0: bad GMP version" >&2
              exit 1
            fi
            printf "[GMP %s]\n" "$gmpvers" >> "$out"
          fi
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
        dotee "$mj" mpfrtests.makeout
        rm mpfrtests.makeout
        echo "*** Running make check ***"
        dotee "$mj check" mpfrtests.makeout
        # Note: We need to remove the possible CR characters, as produced
        # by checks under Wine. But the sed from Solaris does not support
        # \r or even [:cntrl:]; indeed, neither of the following works:
        #   printf "a\rb\n" | sed -n "s/\r//p"
        #   printf "a\rb\n" | sed -n "s/[[:cntrl:]]//p"
        # while GNU sed 4.2.2 is fine even with the --posix option.
        # But we can do:
        #   printf "a\rb\n" | sed -n "s/$(printf \\r)//p"
        sed -n "/: tzeta_ui/,/tests passed/ {
                  s/^\(\[tversion\].*[^$cr]\)$cr*/\1/p
                  s/^\(.*tests passed\)/--> \1/p
                  / PASS:/,/ FAIL:/H
                  / ERROR:/ {
                    g
                    s!.* PASS: *\([0-9]\{1,\}\).* SKIP: *\([0-9]\{1,\}\).* FAIL: *\([0-9]\{1,\}\).*!--> PASS: \1 / SKIP: \2 / FAIL: \3!p
                  }
                }" mpfrtests.makeout >> "$out"
        echo "*** Running make check-gmp-symbols ***"
        if ! grep -q check-gmp-symbols: Makefile; then
          echo "Feature not present. Nothing to do."
        elif grep -q "GMP internals = yes" mpfrtests.makeout; then
          echo "GMP internals have been requested. Test disabled."
        else
          dotee "$mj check-gmp-symbols" mpfrtests.makeout
          echo "Checked that no internal GMP symbols are used." >> "$out"
        fi
        echo "*** Cleaning up ***"
        if [ -z "$1" ]; then
          rm mpfrtests.makeout
          ${MAKE:-make} distclean
        else
          cd ..
          rm -rf obj
        fi
        [ -z "$env" ] || eval "$env"
        unset check || true
        ntests=$((ntests+1))
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

ntests=0
svnvers=""

if [ -x configure ]; then
  # Here the temporary directory is not used by the script itself;
  # it is created in case it is used by mpfrtests.data commands.
  mktmpdir
  [ ! -f Makefile ] || ${MAKE:-make} distclean
  if [ -d .svn ]; then
    svnvers=r$(svnversion)
    [ "$svnvers" != "rUnversioned directory" ] || svnvers=""
  fi
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

lineout
printf "\n$ed\n" >> "$out"

printf "OK, output in %s\n" "$out"
exit 0

# $Id: mpfrtests.sh 103987 2017-12-01 12:59:56Z vinc17/cventin $
