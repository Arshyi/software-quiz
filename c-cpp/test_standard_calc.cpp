#include "stdio.h"
#include "cutest/CuTest.h"
#include "standard_calc.h"

/**************** Tests for bound_to_180() *******************/

void test_bound_basic1(CuTest *tc) {
    CuAssertDblEquals(tc, 0, bound_to_180(0), 0.0001);
}

void test_bound_basic2(CuTest *tc) {
    CuAssertDblEquals(tc, 135, bound_to_180(135), 0.0001);
}

void test_bound_over_180(CuTest *tc) {
    CuAssertDblEquals(tc, -160, bound_to_180(200), 0.0001);
}

void test_bound_exact_180(CuTest *tc) {
    CuAssertDblEquals(tc, -180, bound_to_180(180), 0.0001);
}

void test_bound_negative_overflow(CuTest *tc) {
    CuAssertDblEquals(tc, 160, bound_to_180(-200), 0.0001);
}

void test_bound_multiple_rotations(CuTest *tc) {
    CuAssertDblEquals(tc, -160, bound_to_180(560), 0.0001);
}


/**************** Tests for is_angle_between() *******************/

void test_between_basic1(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 1, 2));
}

void test_between_basic2(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 45, 90));
}

void test_between_false_example(CuTest *tc) {
    CuAssertTrue(tc, !is_angle_between(45, 90, 270));
}

void test_between_wraparound(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(170, -180, -170));
}

void test_between_wraparound_false(CuTest *tc) {
    CuAssertTrue(tc, !is_angle_between(170, 0, -170));
}

void test_between_reversed_bounds(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(90, 45, 0));
}

void test_between_equal_first(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 0, 90));
}

void test_between_equal_second(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(0, 90, 90));
}

void test_between_wraparound_positive_angles(CuTest *tc) {
    CuAssertTrue(tc, is_angle_between(350, 0, 10));
}


int main(int argc, char const *argv[]) {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, test_bound_basic1);
    SUITE_ADD_TEST(suite, test_bound_basic2);
    SUITE_ADD_TEST(suite, test_bound_over_180);
    SUITE_ADD_TEST(suite, test_bound_exact_180);
    SUITE_ADD_TEST(suite, test_bound_negative_overflow);
    SUITE_ADD_TEST(suite, test_bound_multiple_rotations);

    SUITE_ADD_TEST(suite, test_between_basic1);
    SUITE_ADD_TEST(suite, test_between_basic2);
    SUITE_ADD_TEST(suite, test_between_false_example);
    SUITE_ADD_TEST(suite, test_between_wraparound);
    SUITE_ADD_TEST(suite, test_between_wraparound_false);
    SUITE_ADD_TEST(suite, test_between_reversed_bounds);
    SUITE_ADD_TEST(suite, test_between_equal_first);
    SUITE_ADD_TEST(suite, test_between_equal_second);
    SUITE_ADD_TEST(suite, test_between_wraparound_positive_angles);

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return suite->failCount > 0 ? 1 : 0;
}
