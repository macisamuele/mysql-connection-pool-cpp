/*
 * MemoryTracer.h
 *
 *  Created on: May 9, 2016
 *      Author: samuele
 */

#ifndef MACISAMUELE_MEMORYTRACER_H_
#define MACISAMUELE_MEMORYTRACER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <config.h>
#include <sys/types.h>      // for size_t definition

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 * Code from: http://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
 */
size_t getPeakResidentMemory();

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentResidentMemory();

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifdef MEMORY_TRACER_ON
#define CONSTRUCTOR(obj) MEMORY_TRACER_INFO(constructor, obj)
#define DESTRUCTOR(obj) MEMORY_TRACER_INFO(destructor, obj)
#ifdef __cplusplus
#include <iostream>         // for std::cerr handling
#define MEMORY_TRACER_INFO(function, obj) std::cerr << "Tracer: "#function " function " << __PRETTY_FUNCTION__ << " " << __FILE__ << ":" << __LINE__ << " object = " << obj << " | " << getCurrentResidentMemory() << "/" << getPeakResidentMemory() << std::endl
#else
#include <stdio.h>          // for stderr definition
#define MEMORY_TRACER_INFO(function, obj) fprintf(stderr, "Tracer: " # function " function %s %s:%d object = %p | %lu/%lu\n", __PRETTY_FUNCTION__, __FILE__, __LINE__, obj, getCurrentResidentMemory(), getPeakResidentMemory())
#endif
#else
#define CONSTRUCTOR(obj)
#define DESTRUCTOR(obj)
#endif

#endif /* MACISAMUELE_MEMORYTRACER_H_ */
