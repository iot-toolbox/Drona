cmake_minimum_required(VERSION 3.0)
project(dronaSrcLibSoftwareStack)


set(projectName dronasoftwarestack)

#list of all p sources with relative paths
set(pfiles
    ../PSrc/POrb/POrb.p
)

#list of all formula files to be linked (only files names)
set(formulafiles
    POrb.4ml POrbTopics.4ml POrbInterface.4ml)


#######################################
## Generic compilation script for P code
########################################

p_compile(${projectName} pfiles)
p_link(${projectName} formulafiles)
p_add_linker_dependencies(${projectName} pfiles)

## Declare the output
## Declare the output
FILE(GLOB_RECURSE ${projectName}_psources PSrc/*)
FILE(GLOB_RECURSE ${projectName}_csources Src/*)
FILE(GLOB_RECURSE ${projectName}_gsources Generated/*.c)
FILE(GLOB_RECURSE ${projectName}_includes Includes/*)
add_library(${projectName} SHARED
  ${${projectName}_gsources}
  ${${projectName}_csources}
  ${${projectName}_psources}
  ${${projectName}_includes}
)

add_dependencies(${projectName} linker_${projectName})

set_property(TARGET ${projectName} PROPERTY C_STANDARD 99)

set(floatincludes ${drona_SOURCE_DIR}/Src/Lib/PFloat32/Generated/)
target_include_directories(${projectName} PRIVATE
  ${${projectName}_INCLUDE_DIRS}
)

target_link_libraries(${projectName}
  ${${projectName}_LINK_LIBS}
  pthread
  logger
  communication
  pfloat32
  px4driver
)

SET_TARGET_PROPERTIES (
    ${projectName}
    PROPERTIES LINKER_LANGUAGE CXX
)
