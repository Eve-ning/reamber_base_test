#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include <iostream>
#include <codecvt>
#include <filesystem>

// Easier output to Logger
#define Log(msg) Logger::WriteMessage(msg)

namespace reamber_base_test
{	
	TEST_CLASS(object_helper_test_class) {
		TEST_METHOD(trim_editor_hit_object_test) {
			std::string str = "12:23:345 (123|4,234|5) -";
			std::string str_expected = "123|4,234|5";
			str = hit_object::trim_editor_hit_object(str);
			Assert::AreEqual(str_expected, str);
		}
	};
	TEST_CLASS(object_test_class)
	{
	public:
		
		TEST_METHOD(hit_object_raw_loading_test)
		{
			hit_object ho;
			std::string load_str = "64,192,1000,1,0,0:0:0:0:";
			ho.load_raw_hit_object(load_str, 4);

			hit_object ho_expected;
			ho_expected.load_parameters(
				0, 192, 1000, 1, osu_object::sample_set::AUTO,
				0, osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
				osu_object::sample_set::AUTO, 0, "",4);

			Assert::IsTrue(ho_expected == ho);
		}
		TEST_METHOD(timing_point_raw_load_test)
		{
			timing_point tp;
			std::string load_str = "0,200,4,0,0,50,1,0";
				tp.load_raw_timing_point(load_str);

			timing_point tp_expected;
			tp_expected.load_parameters(0, 300, 4, osu_object::sample_set::AUTO, 0, 50, 1, 0);

			Assert::IsTrue(tp_expected == tp);
		}
		TEST_METHOD(hit_object_editor_loading_test)
		{
			hit_object ho;
			std::string load_str = "00:01:000 (1000|0) - ";
			ho.load_editor_hit_object(load_str, 4);

			hit_object ho_expected;
			ho_expected.load_parameters(
				0, 192, 1000, 1, osu_object::sample_set::AUTO,
				0, osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
				osu_object::sample_set::AUTO, 50, "", 4);

			Assert::IsTrue(ho_expected == ho);

		}

		TEST_METHOD(hit_object_v_raw_loading_test);
		TEST_METHOD(timing_point_v_raw_loading_test);
		TEST_METHOD(hit_object_v_editor_loading_test);

	};
}