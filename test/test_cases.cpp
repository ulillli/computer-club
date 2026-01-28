#include <gtest.h>
#include <solver.h>
#include <utility>

TEST(time, can_create_struct_from_string)
{
	Time t("12:22");
	EXPECT_EQ(1, t.minutes==22 && t.hours==12);
}
TEST(time, can_create_struct_from_int)
{
	Time t(134);
	EXPECT_EQ(1, t.minutes==14 && t.hours==2);
}
TEST(time, operator_minus_checking)
{
	Time t1("12:22"), t2("15:24");
	EXPECT_EQ(182,t2-t1);
}
TEST(time, func_getMinutes_checking)
{
	Time t1("12:22");
	EXPECT_EQ(742,t1.getMinutes());
}
TEST(Solver, func_timeCheck_checking_with_wrong_number_in_hours)
{
	Solver s(" ");
	EXPECT_NE(1,s.timeCheck("29:22"));
}
TEST(Solver, func_timeCheck_checking_with_wrong_number_in_minutes)
{
	Solver s(" ");
	EXPECT_NE(1,s.timeCheck("09:89"));
}
TEST(Solver, func_timeCheck_checking_with_wrong_format)
{
	Solver s(" ");
	EXPECT_NE(1,s.timeCheck("9:09"));
}
TEST(Solver, func_nameCheck_checking)
{
	Solver s(" ");
	EXPECT_NE(1,s.nameCheck("client 1"));
}
