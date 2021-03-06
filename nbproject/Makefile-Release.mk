#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Engine/Game.o \
	${OBJECTDIR}/src/Engine/Log.o \
	${OBJECTDIR}/src/Graphics/ConsoleSprite.o \
	${OBJECTDIR}/src/Graphics/Frame.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/asciimon.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/asciimon.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/asciimon ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Engine/Game.o: src/Engine/Game.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Engine/Game.o src/Engine/Game.cpp

${OBJECTDIR}/src/Engine/Log.o: src/Engine/Log.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Engine
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Engine/Log.o src/Engine/Log.cpp

${OBJECTDIR}/src/Graphics/ConsoleSprite.o: src/Graphics/ConsoleSprite.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Graphics/ConsoleSprite.o src/Graphics/ConsoleSprite.cpp

${OBJECTDIR}/src/Graphics/Frame.o: src/Graphics/Frame.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Graphics
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Graphics/Frame.o src/Graphics/Frame.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
