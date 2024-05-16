/*
 * This header guard prevents multiple inclusions of the "main.h" header file.
 */
#ifndef MAIN_H
#define MAIN_H

/*
 * Include the header files for module 1 and module 2.
 */
#include "module1/module1.h"
#include "module2/module2.h"

/*
 * Declaration of the setup and loop functions.
 * These functions are defined in the main source file.
 */
static inline void setup();
static inline void loop();

#endif
