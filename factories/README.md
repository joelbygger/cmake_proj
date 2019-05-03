
# Target factories

All your build targets should be created via a factory here, see comments in the *.cmake file for more info.

* For executables and libraries: [executables_and_libs.cmake](executable_and_lib.cmake)
* For unit test (executables): [utest.cmake](utest.cmake)

The following files are used by the factories:

* Definitions of variables used by factories:
  * Compiler flags and additional features are configured in [settings/flags.cmake](settings/flags.cmake). Only defines variables, does not assign anything to targets.
* Helper functions called by factories:
  * Adds build step to remove symbols from built binary [helpers/strip_symbols.cmake](helpers/strip_symbols.cmake)
  * Adds build flags, 3rd party tools etc. to target build [helpers/set_common_target_stuff.cmake](helpers/set_common_target_stuff.cmake)