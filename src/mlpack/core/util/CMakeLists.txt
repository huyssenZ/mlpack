# Define the files we need to compile.
# Anything not in this list will not be compiled into mlpack.
set(SOURCES
  arma_config.hpp
  arma_config_check.hpp
  backtrace.hpp
  backtrace.cpp
  cli.hpp
  cli.cpp
  cli_deleter.hpp
  cli_deleter.cpp
  cli_impl.hpp
  default_param.hpp
  default_param_impl.hpp
  deprecated.hpp
  log.hpp
  log.cpp
  nulloutstream.hpp
  option.hpp
  option.cpp
  output_param.hpp
  output_param_impl.hpp
  param_data.hpp
  param_data_impl.hpp
  prefixedoutstream.hpp
  prefixedoutstream.cpp
  prefixedoutstream_impl.hpp
  print_param.hpp
  print_param_impl.hpp
  sfinae_utility.hpp
  singletons.hpp
  singletons.cpp
  string_type_param.hpp
  string_type_param_impl.hpp
  timers.hpp
  timers.cpp
  version.hpp
  version.cpp
)

# add directory name to sources
set(DIR_SRCS)
foreach(file ${SOURCES})
  set(DIR_SRCS ${DIR_SRCS} ${CMAKE_CURRENT_SOURCE_DIR}/${file})
endforeach()
# Append sources (with directory name) to list of all mlpack sources (used at
# the parent scope).
set(MLPACK_SRCS ${MLPACK_SRCS} ${DIR_SRCS} PARENT_SCOPE)
