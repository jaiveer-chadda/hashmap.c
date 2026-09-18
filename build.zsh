#!/usr/bin/env zsh

function -- () {
  local -r _root="${${(%):-%x}:a:h}"
  local -r CC='clang'

  local -ra CFLAGS=( O0 g )
  local -ra WARNINGS=( all extra pedantic vla )

  local -r TARGET="$_root/out/${_root:t}"
  local -ra CMD=( "$TARGET" "$@" )

  local -ra SOURCE_FILES=( "$_root/source/"**/*.c )
  local -ra INCLUDES=( "$_root/source/" )

  local -ra SANITISE=( address undefined )
  local -ra ASAN_OPTS=(
    print_legend=0
    stack_trace_format=$'"  %n\t%f\t\t%S"'
  )

  local -a BUILD_ARGS

  if (( $#CFLAGS     )) BUILD_ARGS+=(  "-${(@)^CFLAGS}"      )
  if (( $#WARNINGS   )) BUILD_ARGS+=( "-W${(@)^WARNINGS}"    )
  if (( $#INCLUDES   )) BUILD_ARGS+=( "-I${(@)^INCLUDES}"    )
  if (( $#FRAMEWORKS )) BUILD_ARGS+=( "-framework ${(@)^FRAMEWORKS}" )
  if (( $#SANITISE   )) BUILD_ARGS+=( "-fsanitize=${(j:,:)SANITISE}" )

  BUILD_ARGS+=( --output "$TARGET" -- "${(@)SOURCE_FILES}" )

  "$CC" "${(@)BUILD_ARGS}" \
    && ASAN_OPTIONS="${(j.:.)ASAN_OPTS}" "${(@)CMD}"

} "$@"

# spell:ignoreRegExp /\b[A-Z_]+\b/g
