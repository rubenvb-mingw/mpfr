#!/bin/sh

# Test of MPFR tarballs with various options.
# Written in 2011-2012 by Vincent Lefevre.
#
# Usage: ./mpfrtests.sh [ +<host> ] [ <archive.tar.gz> ] < mpfrtests.data
#    or  ./mpfrtests.sh -C
#
# In normal use (first form):
#   A +<host> argument can be needed when the FQDN is not set correctly.
#   The default <archive.tar.gz> value is "mpfr-tests.tar.gz".
#   A file mpfrtests.<host>.out is output.
# With the -C option (second form):
#   Clean-up: Any temporary mpfrtests directory is removed (such
#   a directory isn't removed automatically in case of abnormal
#   termination, in order to be able to debug).

# For the Solaris /bin/sh
{ a=a; : ${a%b}; } 2> /dev/null || test ! -x /usr/xpg4/bin/sh || \
  exec /usr/xpg4/bin/sh -- "$0" ${1+"$@"}

prefix="/tmp/mpfrtests-$USER-"

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
    case "$line" in
      PROC:*)
	[ -n "$first" ]
        echo "* $fqdn ($(${1:-.}/config.guess) / ${line#PROC:})" > "$out"
        [ -z "$1" ] || echo "with objdir != srcdir" >> "$out"
        echo "MPFR version: $(cat ${1:-.}/VERSION)" >> "$out"
        unset conf || true
	;;
      ENV:*)
        v="${line#ENV:}"
        export "$v"
        env="$env ${v%=*}"
        ;;
      CONF:*)
        if [ -z "$conf" ]; then
          if [ -z "$1" ]; then
            conf="./configure"
          else
            mkdir obj
            cd obj
            conf="../$1/configure"
          fi
          envvars=""
        fi
        conf="$conf '${line#CONF:}'"
        ;;
      INFO:*)
        if [ -n "$conf" ]; then
          echo '$ ./config.status -V' >> "$out"
          dotee "$conf" mpfrtests.cfgout
          ./config.status -V | sed '/with options/q' >> "$out"
          gmpvers=$(sed -n "s/$gmprx/\1/p" mpfrtests.cfgout)
          [ -n "$gmpvers" ]
          printf "[GMP %s]\n" "$gmpvers" >> "$out"
          rm mpfrtests.cfgout
          unset conf || true
        fi
        cmd=${line#INFO:}
        printf "\$ %s\n" "${cmd% | head -n 1}" >> "$out"
        eval $cmd >> "$out"
        ;;
      CHECK)
        [ -z "$conf" ]
        eval $mj
        dotee "$mj check" mpfrtests.makeout
        sed -n "/: tzeta_ui/,/tests passed/ {
                  s/^.*\(MPFR tuning parameters.*\)/[\1]/p
                  s/^\(.*tests passed\)/--> \1/p
                }" mpfrtests.makeout >> "$out"
        if [ -z "$1" ]; then
          rm mpfrtests.makeout
          make distclean
        else
          cd ..
          rm -rf obj
        fi
        [ -z "$env" ] || unset $env
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

if [ -x configure ]; then
  tstall
elif [ -f "$tgz" ]; then
  tmpdir="${prefix}$$"
  rm -rf "$tmpdir"
  mkdir "$tmpdir"
  chmod 700 "$tmpdir"
  [ ! -h "$tmpdir" ]
  cd "$tmpdir"
  case "$tgz" in
    /*) ;;
    *) tgz="$pwd/$tgz" ;;
  esac
  gunzip -c "$tgz" | tar xf -
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

# $Id: mpfrtests.sh 53113 2012-07-07 01:33:54Z vinc17/xvii $
