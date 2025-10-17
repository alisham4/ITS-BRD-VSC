# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/1"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/tmp"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/src/Stack.Debug+ITSboard-stamp"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/src"
  "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/src/Stack.Debug+ITSboard-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/src/Stack.Debug+ITSboard-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/alishamuzaffar/GitProjekte/ITS-BRD-VSC/Programs/Stack/tmp/Stack.Debug+ITSboard/src/Stack.Debug+ITSboard-stamp${cfgdir}") # cfgdir has leading slash
endif()
