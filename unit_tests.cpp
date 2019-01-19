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
	TEST_CLASS(object_helper_class)
	{
	public:
		TEST_METHOD(trim_editor_hit_object) {
			
			Assert::AreEqual(std::string("1000|1,2000|2"),
				hit_object::trim_editor_hit_object(mocks.editor_hit_object_str_multiple));
		}
	};
	TEST_CLASS(object_class)
	{
	public:
		TEST_METHOD(hit_object_raw_loading)
		{
			hit_object ho;
			ho.load_raw_hit_object(mocks.raw_hit_object_str_note, 4);

			Assert::IsTrue(ho == mocks.hit_object_note);
		}
		TEST_METHOD(timing_point_raw_load)
		{
			timing_point tp;
			tp.load_raw_timing_point(mocks.raw_timing_point_bpm);

			Assert::IsTrue(tp == mocks.timing_point_bpm);
		}
		TEST_METHOD(hit_object_editor_loading)
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

		TEST_METHOD(hit_object_v_raw_loading) {
			hit_object_v ho_v;
			ho_v.load_raw_hit_object(mocks.raw_hit_object_str_multiple, 4);

			Assert::IsTrue(ho_v == mocks.hit_object_multiple);
		}
		TEST_METHOD(timing_point_v_raw_loading) {
			timing_point_v tp_v;
			tp_v.load_raw_timing_point(mocks.raw_timing_point_str_multiple);

			Assert::IsTrue(tp_v == mocks.timing_point_multiple);
		}
		TEST_METHOD(hit_object_v_editor_loading) {
			hit_object_v ho_v;
			ho_v.load_editor_hit_object(mocks.editor_hit_object_str_multiple, 4);

			Assert::IsTrue(ho_v == mocks.editor_hit_object_multiple);
		}
		
		// FOBO: First Object By Offset
		// LOBO: Last  Object By Offset
		TEST_METHOD(fobo_hit_object)
		{
			Assert::IsTrue(
				mocks.hit_object_multiple[0] == // Expect the first object
				mocks.hit_object_multiple.get_first_object_by_offset()
			);
		}
		TEST_METHOD(fobo_timing_point)
		{
			Assert::IsTrue(
				mocks.timing_point_multiple[0] == // Expect the first object
				mocks.timing_point_multiple.get_first_object_by_offset()
			);
		}
		TEST_METHOD(lobo_hit_object)
		{
			Assert::IsTrue(
				mocks.hit_object_multiple[2] == // Expect the first object
				mocks.hit_object_multiple.get_last_object_by_offset()
			);
		}
		TEST_METHOD(lobo_timing_point)
		{
			Assert::IsTrue(
				mocks.timing_point_multiple[2] == // Expect the first object
				mocks.timing_point_multiple.get_last_object_by_offset()
			);
		}

		TEST_METHOD(get_column_v) {
			Assert::IsTrue(mocks.hit_object_multiple.get_column_v() ==
				std::vector<unsigned int>{0, 2, 3});
		}
		TEST_METHOD(get_offset_min_hit_object) {
			Assert::IsTrue(mocks.hit_object_multiple.get_offset_min() == 1000);
		}
		TEST_METHOD(get_offset_max_hit_object) {
			Assert::IsTrue(mocks.hit_object_multiple.get_offset_max() == 3000);
		}
		TEST_METHOD(get_offset_min_timing_point) {
			Assert::IsTrue(mocks.timing_point_multiple.get_offset_min() == 0);
		}
		TEST_METHOD(get_offset_max_timing_point) {
			Assert::IsTrue(mocks.timing_point_multiple.get_offset_max() == 2000);
		}

		TEST_METHOD(sort_by_offset_hit_object) {
			hit_object_v ho_v = mocks.hit_object_multiple;

			// Manually sort by descending
			hit_object_v ho_v_sort_desc = hit_object_v(3);
			ho_v_sort_desc[0] = ho_v[2];
			ho_v_sort_desc[1] = ho_v[1];
			ho_v_sort_desc[2] = ho_v[0];

			// Sort by Descending
			ho_v.sort_by_offset(false);

			Assert::IsTrue(ho_v == ho_v_sort_desc);
		}
		TEST_METHOD(sort_by_offset_timing_point) {
			timing_point_v tp_v = mocks.timing_point_multiple;

			// Manually sort by descending
			timing_point_v tp_v_sort_desc = timing_point_v(3);
			tp_v_sort_desc[0] = tp_v[2];
			tp_v_sort_desc[1] = tp_v[1];
			tp_v_sort_desc[2] = tp_v[0];

			// Sort by Descending
			tp_v.sort_by_offset(false);

			Assert::IsTrue(tp_v == tp_v_sort_desc);
		}
	};

	TEST_CLASS(lib_functions_test_class)
	{
	public:
		TEST_METHOD(lib_get_offset_difference) {
			auto offset_difference =
				lib_functions::get_offset_difference<hit_object>(
					std::make_shared<hit_object_v>(mocks.hit_object_multiple));
			Assert::IsTrue(offset_difference == std::vector<double>{1000, 1000});
		}
		TEST_METHOD(lib_create_copies_singular_hit_object) {
			auto copies = lib_functions::create_copies<hit_object>
				(mocks.hit_object_note, std::vector<double>{1000, 2000});
			Assert::IsTrue(std::vector<double>({ 1000,2000 }) == copies->get_offset_v(false));
		}
		TEST_METHOD(lib_create_copies_multiple_hit_object) {
			auto copies = lib_functions::create_copies<hit_object>
				(std::make_shared<hit_object_v>(mocks.hit_object_multiple), std::vector<double>{1000, 2000});
			// Get unique offset for copies
			Assert::IsTrue(std::vector<double>({ 1000,2000,3000,4000 }) == copies->get_offset_v(true));
		}
		TEST_METHOD(lib_create_copies_singular_timing_point) {
			auto copies = lib_functions::create_copies<timing_point>
				(mocks.timing_point_sv, std::vector<double>{1000, 2000});
			Assert::IsTrue(std::vector<double>({ 1000,2000 }) == copies->get_offset_v(false));
		}
		TEST_METHOD(lib_create_copies_multiple_timing_point) {
			auto copies = lib_functions::create_copies<timing_point>
				(std::make_shared<timing_point_v>(mocks.timing_point_multiple), std::vector<double>{1000, 2000});
			// Get unique offset for copies
			Assert::IsTrue(std::vector<double>({ 1000,2000,3000,4000 }) == copies->get_offset_v(true));
		}
		TEST_METHOD(lib_create_copies_sub_hit_object) {
			auto copies = lib_functions::create_copies_by_subdivision<hit_object>
				(std::vector<double>({ 100,300,500,700,1000 }), mocks.hit_object_note, 3);
			std::vector<std::string> expected = {
				"64,192,100.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1 -
				"64,192,166.666667,1,0,0:0:0:50:hitsound.wav", // Subd 2
				"64,192,233.333333,1,0,0:0:0:50:hitsound.wav", // Subd 3
				"64,192,300.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1 -
				"64,192,366.666667,1,0,0:0:0:50:hitsound.wav", // Subd 2
				"64,192,433.333333,1,0,0:0:0:50:hitsound.wav", // Subd 3
				"64,192,500.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1 -
				"64,192,566.666667,1,0,0:0:0:50:hitsound.wav", // Subd 2
				"64,192,633.333333,1,0,0:0:0:50:hitsound.wav", // Subd 3
				"64,192,700.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1 -
				"64,192,800.000000,1,0,0:0:0:50:hitsound.wav", // Subd 2
				"64,192,900.000000,1,0,0:0:0:50:hitsound.wav", // Subd 3
				"64,192,1000.000000,1,0,0:0:0:50:hitsound.wav" // Subd 1 -
			};
			Assert::IsTrue(copies->get_string_raw_v() == expected);
		}
		TEST_METHOD(lib_create_copies_sub_hit_object_delay) {
			auto copies = lib_functions::create_copies_by_subdivision<hit_object>
				(std::make_shared<hit_object_v>(mocks.hit_object_multiple), 5, true, false);

			std::vector<std::string> expected = {
				"64,192,1200.000000,1,0,0:0:0:40:hit1.wav",
				"64,192,1400.000000,1,0,0:0:0:40:hit1.wav",
				"64,192,1600.000000,1,0,0:0:0:40:hit1.wav",
				"64,192,1800.000000,1,0,0:0:0:40:hit1.wav",
				"320,192,2200.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
				"320,192,2400.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
				"320,192,2600.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
				"320,192,2800.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
			};

			Assert::IsTrue(copies->get_string_raw_v() == expected);
		}
		TEST_METHOD(lib_create_copies_reldiff) {
			auto copies = lib_functions::create_copies_by_relative_difference(
				std::vector<double>({ 100, 300 }), mocks.hit_object_note, 0.25, true);

			std::vector<std::string> expected = {
				"64,192,100.000000,1,0,0:0:0:50:hitsound.wav",
				"64,192,150.000000,1,0,0:0:0:50:hitsound.wav",
				"64,192,300.000000,1,0,0:0:0:50:hitsound.wav"
			};
			Assert::IsTrue(copies->get_string_raw_v() == expected);
		}
		TEST_METHOD(lib_create_copies_reldiff_delay) {
			auto copies = lib_functions::create_copies_by_relative_difference<hit_object>
				(std::make_shared<hit_object_v>(mocks.hit_object_multiple), 0.25, true, true);

			std::vector<std::string> expected = {
				"64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
				"64,192,1250.000000,1,0,0:0:0:40:hit1.wav",
				"320,192,2000.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
				"320,192,2250.000000,1,0,2500.000000:0:0:0:50:hit2.wav",
				"448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
			};

			Assert::IsTrue(copies->get_string_raw_v() == expected);
		}
		TEST_METHOD(lib_normalize) {
			auto normalized = lib_functions::create_normalize(mocks.timing_point_multiple, 200, false);
			std::vector<std::string> expected = {
				"0.000000,-200.000000,4,1,1,50,0,0"
			};

			Assert::IsTrue(normalized.get_string_raw_v() == expected);
		}
		TEST_METHOD(lib_create_basic_stutter) {
			auto tp_v = lib_functions::create_basic_stutter(std::vector<double>({ 100,300,700 }), 1.5, 0.25);

			std::vector<std::string> expected = {
				"100.000000,-66.666667,4,0,0,25,0,0",
				"150.000000,-120.000000,4,0,0,25,0,0",
				"300.000000,-66.666667,4,0,0,25,0,0",
				"400.000000,-120.000000,4,0,0,25,0,0",
				"700.000000,-66.666667,4,0,0,25,0,0"
			};

			Assert::IsTrue(tp_v.get_string_raw_v() == expected);
		}

};

}