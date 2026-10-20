//
// Created by ko-artist on 10/19/26.
//

#ifndef THANOS_ASSERT_H
#define THANOS_ASSERT_H

#ifdef DEBUG_MODE
    #define assert(cond) if (!(cond)) { kernelpanic("Assertion failed: %s at file: %s, line: %d", #cond, __FILE__, __LINE__); }
#else
    #define assert(cond)
#endif

#endif //THANOS_ASSERT_H
