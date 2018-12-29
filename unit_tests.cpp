#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
#include <iostream>
#include <codecvt>
#include <filesystem>
#include "../reamber_base/src/custom_lib_functions/lib_functions.h"

// Easier output to Logger
#define Log(msg) Logger::WriteMessage(msg)

class mock_objects {
public:
	mock_objects() {
		hit_object_note.load_parameters(
			0, 192, 1000, 1, osu_object::sample_set::AUTO, 0,
			osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
			osu_object::sample_set::AUTO, 50, "hitsound.wav", 4);
		hit_object_long_note.load_parameters(
			0, 192, 1000, 1, osu_object::sample_set::AUTO, 1500,
			osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
			osu_object::sample_set::AUTO, 50, "hitsound.wav", 4);
		editor_hit_object_singular.load_parameters(1, 1000, 0, 4);
		editor_hit_object_multiple.push_back(hit_object());
		editor_hit_object_multiple.push_back(hit_object());
		editor_hit_object_multiple[0].load_parameters(1, 1000, 0, 4);
		editor_hit_object_multiple[1].load_parameters(2, 2000, 0, 4);
		timing_point_sv.load_parameters(
			1000, 2, 4, osu_object::sample_set::AUTO, 0, 50, false, false
		);
		timing_point_bpm.load_parameters(
			1000, 300, 4, osu_object::sample_set::AUTO, 0, 50, true, false
		);
	}
	std::string raw_hit_object_str_note =
		"64,192,1000,1,0,0:0:0:50:hitsound.wav";
	std::string raw_hit_object_str_long_note =
		"64,192,1000,128,0,1500:0:0:0:50:hitsound.wav";
	std::string raw_timing_point_sv =
		"1000,-50,4,0,0,50,0,0";
	std::string raw_timing_point_bpm =
		"1000,200,4,0,0,50,1,0";
	std::string editor_hit_object_str_singular =
		"00:01:000 (1000|1) -";
	std::string editor_hit_object_str_multiple =
		"00:01:000 (1000|1,2000|2) -";

	hit_object hit_object_note;
	hit_object hit_object_long_note;
	timing_point timing_point_sv;
	timing_point timing_point_bpm;
	hit_object editor_hit_object_singular;
	hit_object_v editor_hit_object_multiple;

};

namespace reamber_base_test
{	
	const mock_objects mocks = mock_objects();
	TEST_CLASS(object_helper_test_class)
	{
	public:
		TEST_METHOD(trim_editor_hit_object_test) {
			
			Assert::AreEqual(std::string("1000|1,2000|2"),
				hit_object::trim_editor_hit_object(mocks.editor_hit_object_str_multiple));
		}
	};
	TEST_CLASS(object_test_class)
	{
	public:
		TEST_METHOD(hit_object_raw_loading_test)
		{
			hit_object ho;
			ho.load_raw_hit_object(mocks.raw_hit_object_str_note, 4);

			Assert::IsTrue(ho == mocks.hit_object_note);
		}
		TEST_METHOD(timing_point_raw_load_test)
		{
			timing_point tp;
			tp.load_raw_timing_point(mocks.raw_timing_point_bpm);

			Assert::IsTrue(tp == mocks.timing_point_bpm);
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

		//TEST_METHOD(hit_object_v_raw_loading_test);
		//TEST_METHOD(timing_point_v_raw_loading_test);
		//TEST_METHOD(hit_object_v_editor_loading_test);

	};
	//TEST_CLASS(lib_functions_test_class)
	//{
	//public:
	//	TEST_METHOD(test)
	//	{
	//		//lib_functions::first_object_by_offset()
	//	}
	//};
}