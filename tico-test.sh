#!/usr/bin/env sh

assert() {
  R="$(./tico "$1")"
  if [ ! "$R" = "$2" ]; then
    echo "error on tico $1"
    echo "  expected $2"
    echo "  actual   $R"
    exit 1
  fi
}

assert "~" "~"
assert "/" "/"
assert "/home/hugopeixoto/work/personal/tico" "/h/h/w/p/tico"
assert "~/work/personal/tico" "~/w/p/tico"
assert "~/work/personal/tico/" "~/w/p/t/"
assert "~/work/ééé/tico" "~/w/é/tico"
assert "~/.config/htop" "~/.c/htop"
