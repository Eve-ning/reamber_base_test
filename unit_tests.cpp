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

		timing_point_sv.load_parameters(
			1000, 2, 4, osu_object::sample_set::AUTO, 0, 50, false, false
		);
		timing_point_bpm.load_parameters(
			1000, 300, 4, osu_object::sample_set::AUTO, 0, 50, true, false
		);

		editor_hit_object_singular.load_parameters(1, 1000, 0, 4);

		editor_hit_object_multiple[0].load_parameters(1, 1000, 0, 4);
		editor_hit_object_multiple[1].load_parameters(2, 2000, 0, 4);

		hit_object_multiple[0].load_parameters(
			0, 192, 1000, 1, osu_object::sample_set::AUTO, 0,
			osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
			osu_object::sample_set::AUTO, 40, "hit1.wav", 4);
		hit_object_multiple[1].load_parameters(
			2, 192, 2000, 1, osu_object::sample_set::AUTO, 2500,
			osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
			osu_object::sample_set::AUTO, 50, "hit2.wav", 4);
		hit_object_multiple[2].load_parameters(
			3, 192, 3000, 1, osu_object::sample_set::AUTO, 0,
			osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
			osu_object::sample_set::AUTO, 60, "hit3.wav", 4);

		timing_point_multiple[0].load_parameters(
			0, 400, 4, osu_object::sample_set::NORMAL, 1, 50, true, false
		);
		timing_point_multiple[1].load_parameters(
			1000, 2, 4, osu_object::sample_set::NORMAL, 1, 50, false, true
		);
		timing_point_multiple[2].load_parameters(
			2000, 0.5, 4, osu_object::sample_set::NORMAL, 1, 50, false, false
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

	std::string raw_hit_object_str_multiple =
		"64,192,1000,1,0,0:0:0:40:hit1.wav\n" // N
		"320,192,2000,128,0,2500:0:0:0:70:hit2.wav\n" // LN
		"448,192,3000,1,0,0:0:0:60:hit3.wav"; // N

	std::string raw_timing_point_str_multiple =
		"0,150,4,1,1,50,1,0\n" // BPM 400
		"1000,-50,4,1,1,50,0,1\n" // SV 2.0 Kiai
		"2000,-200,4,1,1,50,0,0"; // SV 0.50

	hit_object hit_object_note;
	hit_object hit_object_long_note;
	timing_point timing_point_sv;
	timing_point timing_point_bpm;
	hit_object editor_hit_object_singular;
	hit_object_v editor_hit_object_multiple = hit_object_v(2);

	hit_object_v hit_object_multiple = hit_object_v(3);
	timing_point_v timing_point_multiple = timing_point_v(3);

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

		TEST_METHOD(hit_object_v_raw_loading_test) {
			hit_object_v ho_v;
			ho_v.load_raw_hit_object(mocks.raw_hit_object_str_multiple, 4);

			Assert::IsTrue(ho_v == mocks.hit_object_multiple);
		}
		TEST_METHOD(timing_point_v_raw_loading_test) {
			timing_point_v tp_v;
			tp_v.load_raw_timing_point(mocks.raw_timing_point_str_multiple);

			Assert::IsTrue(tp_v == mocks.timing_point_multiple);
		}
		TEST_METHOD(hit_object_v_editor_loading_test) {
			hit_object_v ho_v;
			ho_v.load_editor_hit_object(mocks.editor_hit_object_str_multiple, 4);

			Log(ho_v[0].get_raw_hit_object().c_str());
			Log(mocks.editor_hit_object_multiple[0].get_raw_hit_object().c_str());
			

			Log(ho_v[1].get_raw_hit_object().c_str());
			Log(mocks.editor_hit_object_multiple[1].get_raw_hit_object().c_str());

			Assert::IsTrue(ho_v == mocks.editor_hit_object_multiple);
		}

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