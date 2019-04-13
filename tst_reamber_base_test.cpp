#include <QtTest>

// add necessary includes here
#include <iostream>
#include <vector>
#include <amber_f/lib_functions.h>
#include <QDebug>

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
            0, 192, 1000, hit_object::NORMAL, osu_object::sample_set::AUTO, 0,
            osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
            osu_object::sample_set::AUTO, 40, "hit1.wav", 4);
        hit_object_multiple[1].load_parameters(
            2, 192, 2000, hit_object::LN, osu_object::sample_set::AUTO, 2500,
            osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
            osu_object::sample_set::AUTO, 50, "hit2.wav", 4);
        hit_object_multiple[2].load_parameters(
            3, 192, 3000, hit_object::NORMAL, osu_object::sample_set::AUTO, 0,
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

class reamber_base_test : public QObject
{
    Q_OBJECT


private slots:
    void trim_editor_hit_object();
    void hit_object_raw_loading();
    void timing_point_raw_load();
    void hit_object_editor_loading();
    void hit_object_v_raw_loading();
    void timing_point_v_raw_loading();
    void hit_object_v_editor_loading();

    void fobo_hit_object();
    void fobo_timing_point();
    void lobo_hit_object();
    void lobo_timing_point();

    void get_column_v();
    void get_offset_min_hit_object();
    void get_offset_max_hit_object();
    void get_offset_min_timing_point();
    void get_offset_max_timing_point();

    void sort_by_offset_hit_object();
    void sort_by_offset_timing_point();

    void timing_point_v_multiply();
    void timing_point_v_get_ave();

    void timing_point_v_arithmetic();

    void lib_offset_diff();
    void lib_create_copies_singular_hit_object();
    void lib_create_copies_multiple_hit_object();
    void lib_create_copies_singular_timing_point();
    void lib_create_copies_multiple_timing_point();
    void lib_create_copies_sub_by_hit_object();
    void lib_create_copies_sub_by_hit_object_delay();
    void lib_create_copies_sub_to_hit_object();
    void lib_create_copies_sub_to_hit_object_delay();
    void lib_create_copies_reldiff();
    void lib_create_copies_reldiff_delay();
    void lib_create_copies_absdiff();
    void lib_create_copies_absdiff_delay();
    void lib_normalize();
    void lib_create_stutter_relative();
    void lib_create_stutter_absolute();
    void lib_create_stutter_from_offset();
    void lib_extract_nth();
    void lib_delete_nth();

private:
    mock_objects mocks = mock_objects();

};

void reamber_base_test::trim_editor_hit_object() {

    std::string str = mocks.editor_hit_object_str_multiple;
    hit_object::trim_editor_hit_object(str);
    QVERIFY(std::string("1000|1,2000|2") == str);
}
void reamber_base_test::hit_object_raw_loading()
{
    hit_object ho;
    ho.load_raw_hit_object(mocks.raw_hit_object_str_note, 4);

    QVERIFY(ho == mocks.hit_object_note);
}
void reamber_base_test::timing_point_raw_load()
{
    timing_point tp;
    tp.load_raw_timing_point(mocks.raw_timing_point_bpm);

    QVERIFY(tp == mocks.timing_point_bpm);
}
void reamber_base_test::hit_object_editor_loading()
{
    hit_object ho;
    std::string load_str = "00:01:000 (1000|0) - ";
    ho.load_editor_hit_object(load_str, 4);

    hit_object ho_expected;
    ho_expected.load_parameters(
                0, 192, 1000, 1, osu_object::sample_set::AUTO,
                0, osu_object::sample_set::AUTO, osu_object::sample_set::AUTO,
                osu_object::sample_set::AUTO, 50, "", 4);

    QVERIFY(ho_expected == ho);

}

void reamber_base_test::hit_object_v_raw_loading() {
    hit_object_v ho_v;
    ho_v.load_raw_hit_object(mocks.raw_hit_object_str_multiple, 4);

    QVERIFY(ho_v == mocks.hit_object_multiple);
}
void reamber_base_test::timing_point_v_raw_loading() {
    timing_point_v tp_v;
    tp_v.load_raw_timing_point(mocks.raw_timing_point_str_multiple);

    QVERIFY(tp_v == mocks.timing_point_multiple);
}
void reamber_base_test::hit_object_v_editor_loading() {
    hit_object_v ho_v;
    qDebug() << ho_v.load_editor_hit_object(mocks.editor_hit_object_str_multiple, 4);

    QVERIFY(ho_v == mocks.editor_hit_object_multiple);
}

// FOBO: First Object By Offset
// LOBO: Last  Object By Offset
void reamber_base_test::fobo_hit_object()
{
    QVERIFY(
                mocks.hit_object_multiple[0] == // Expect the first object
            mocks.hit_object_multiple.get_first_object_by_offset()
            );
}
void reamber_base_test::fobo_timing_point()
{
    QVERIFY(
                mocks.timing_point_multiple[0] == // Expect the first object
            mocks.timing_point_multiple.get_first_object_by_offset()
            );
}
void reamber_base_test::lobo_hit_object()
{
    QVERIFY(
                mocks.hit_object_multiple[2] == // Expect the first object
            mocks.hit_object_multiple.get_last_object_by_offset()
            );
}
void reamber_base_test::lobo_timing_point()
{
    QVERIFY(
                mocks.timing_point_multiple[2] == // Expect the first object
            mocks.timing_point_multiple.get_last_object_by_offset()
            );
}

void reamber_base_test::get_column_v() {
    QVERIFY((mocks.hit_object_multiple.get_column_v() ==
            std::vector<unsigned int>{0, 2, 3}));
}
void reamber_base_test::get_offset_min_hit_object() {
    QVERIFY(mocks.hit_object_multiple.get_offset_min() == 1000.0);
}
void reamber_base_test::get_offset_max_hit_object() {
    QVERIFY(mocks.hit_object_multiple.get_offset_max() == 3000.0);
}
void reamber_base_test::get_offset_min_timing_point() {
    QVERIFY(mocks.timing_point_multiple.get_offset_min() == 0.0);
}
void reamber_base_test::get_offset_max_timing_point() {
    QVERIFY(mocks.timing_point_multiple.get_offset_max() == 2000.0);
}

void reamber_base_test::sort_by_offset_hit_object() {
    hit_object_v ho_v = mocks.hit_object_multiple;

    // Manually sort by descending
    hit_object_v ho_v_sort_desc = hit_object_v(3);
    ho_v_sort_desc[0] = ho_v[2];
    ho_v_sort_desc[1] = ho_v[1];
    ho_v_sort_desc[2] = ho_v[0];

    // Sort by Descending
    ho_v.sort_by_offset(false);

    QVERIFY(ho_v == ho_v_sort_desc);
}
void reamber_base_test::sort_by_offset_timing_point() {
    timing_point_v tp_v = mocks.timing_point_multiple;

    // Manually sort by descending
    timing_point_v tp_v_sort_desc = timing_point_v(3);
    tp_v_sort_desc[0] = tp_v[2];
    tp_v_sort_desc[1] = tp_v[1];
    tp_v_sort_desc[2] = tp_v[0];

    // Sort by Descending
    tp_v.sort_by_offset(false);

    QVERIFY(tp_v == tp_v_sort_desc);
}

void reamber_base_test::timing_point_v_multiply() {
    //        [0] [1] [2] [3] [4]
    // SELF :  1   1           1
    // EFF  :  1       1   1
    timing_point_v tp_v(4);

    tp_v[0].load_parameters(0, 1, false);
    tp_v[1].load_parameters(1, 2, false);
    tp_v[2].load_parameters(4, 4, false);
    tp_v[3].load_parameters(5, 8, false);
    timing_point_v tp_v_eff(3);

    tp_v_eff[0].load_parameters(0, 1, false);
    tp_v_eff[1].load_parameters(2, 0.5, false);
    tp_v_eff[2].load_parameters(3, 0.25, false);

    tp_v.cross_effect_multiply(tp_v_eff);

    std::vector<std::string> expected = {
        "0.000000,-100.000000,4,0,0,25,0,0",
        "1.000000,-50.000000,4,0,0,25,0,0",
        "4.000000,-100.000000,4,0,0,25,0,0",
        "5.000000,-50.000000,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);
}
void reamber_base_test::timing_point_v_get_ave() {
    // SV
    timing_point_v tp_v = timing_point_v(3);
    tp_v[0].load_parameters(0, 1.5, false);
    tp_v[1].load_parameters(100, 0.5, false);
    tp_v[2].load_parameters(400, 1.75, false);

    QVERIFY(0.75 == tp_v.get_average_sv_value());

    // BPM
    tp_v = timing_point_v(3);
    tp_v[0].load_parameters(0, 200, true);
    tp_v[1].load_parameters(100, 100, true);
    tp_v[2].load_parameters(400, 150, true);

    QVERIFY(125.0 == tp_v.get_average_bpm_value());

    // MIXED
    tp_v = timing_point_v(4);
    tp_v[0].load_parameters(0, 200, true);
    tp_v[1].load_parameters(50, 0.5, false); // JUNK SV
    tp_v[2].load_parameters(100, 100, true);
    tp_v[3].load_parameters(400, 150, true);

    QVERIFY(125.0 == tp_v.get_average_bpm_value());
}

void reamber_base_test::timing_point_v_arithmetic()
{
    // +
    timing_point_v tp_v = timing_point_v(3);
    tp_v[0].load_parameters(0, 1.5, false);
    tp_v[1].load_parameters(100, 0.5, false);
    tp_v[2].load_parameters(400, 1.75, false);

    tp_v += 2;

    for (auto tp : tp_v) {
        qDebug() << tp.get_string_raw().c_str();
    }

    QVERIFY(true);
}

void reamber_base_test::lib_offset_diff() {
    auto offset_difference =
            amber_f::offset_diff<hit_object>(&mocks.hit_object_multiple);
    QVERIFY(offset_difference == std::vector<double>({1000, 1000}));
}
void reamber_base_test::lib_create_copies_singular_hit_object() {
    auto copies = amber_f::copy<hit_object>
            (mocks.hit_object_note, std::vector<double>{1000, 2000});
    QVERIFY(std::vector<double>({ 1000,2000 }) == copies->get_offset_v(false));
}
void reamber_base_test::lib_create_copies_multiple_hit_object() {
    auto copies = amber_f::copy<hit_object>
            (&mocks.hit_object_multiple, std::vector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(std::vector<double>({ 1000,2000,3000,4000 }) == copies->get_offset_v(true));
}
void reamber_base_test::lib_create_copies_singular_timing_point() {
    auto copies = amber_f::copy<timing_point>
            (mocks.timing_point_sv, std::vector<double>{1000, 2000});
    QVERIFY(std::vector<double>({ 1000,2000 }) == copies->get_offset_v(false));
}
void reamber_base_test::lib_create_copies_multiple_timing_point() {
    auto copies = amber_f::copy<timing_point>
            (&mocks.timing_point_multiple, std::vector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(std::vector<double>({ 1000,2000,3000,4000 }) == copies->get_offset_v(true));
}
void reamber_base_test::lib_create_copies_sub_by_hit_object() {
    // EXCLUDE
    auto copies = amber_f::copy_subd_by<hit_object>
            (std::vector<double>({ 100,300,500 }), mocks.hit_object_note, 2, false);

    std::vector<std::string> expected = {
        "64,192,166.666667,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,233.333333,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,366.666667,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,433.333333,1,0,0:0:0:50:hitsound.wav", // Subd 2
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // INCLUDE
    copies = amber_f::copy_subd_by<hit_object>
            (std::vector<double>({ 100,300,500 }), mocks.hit_object_note, 2, true);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,166.666667,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,233.333333,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,366.666667,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,433.333333,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,500.000000,1,0,0:0:0:50:hitsound.wav"  // Subd 0
    };

    QVERIFY(copies->get_string_raw_v() == expected);
}
void reamber_base_test::lib_create_copies_sub_by_hit_object_delay() {
    auto copies = amber_f::copy_subd_by(
                &mocks.hit_object_multiple, 4, false);

    std::vector<std::string> expected = {
        "64,192,1200.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1400.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1600.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1800.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2200.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2400.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2600.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2800.000000,128,0,2500.000000:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    copies = amber_f::copy_subd_by(
                &mocks.hit_object_multiple, 4, true);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1200.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1400.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1600.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1800.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2200.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2400.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2600.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2800.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

}
void reamber_base_test::lib_create_copies_sub_to_hit_object() {
    // EXCLUDE
    auto copies = amber_f::copy_subd_to<hit_object>
            (std::vector<double>({ 100,300,500 }), mocks.hit_object_note, 50, false);

    std::vector<std::string> expected = {
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,200.000000,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,250.000000,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,350.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,400.000000,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,450.000000,1,0,0:0:0:50:hitsound.wav"  // Subd 3
    };

    for (auto ho : *copies) {
        qDebug() << ho.get_string_raw().c_str();
    }

    QVERIFY(copies->get_string_raw_v() == expected);

    // INCLUDE
    copies = amber_f::copy_subd_to<hit_object>
            (std::vector<double>({ 100,300,500 }), mocks.hit_object_note, 50, true);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,200.000000,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,250.000000,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,350.000000,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,400.000000,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,450.000000,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,500.000000,1,0,0:0:0:50:hitsound.wav"  // Subd 0
    };

    for (auto ho : *copies) {
        qDebug() << ho.get_string_raw().c_str();
    }

    QVERIFY(copies->get_string_raw_v() == expected);
}
void reamber_base_test::lib_create_copies_sub_to_hit_object_delay() {
    auto copies = amber_f::copy_subd_to(
                &mocks.hit_object_multiple, 250, false);

    std::vector<std::string> expected = {
        "64,192,1250.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1500.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1750.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2250.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2500.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2750.000000,128,0,2500.000000:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    copies = amber_f::copy_subd_to(
                &mocks.hit_object_multiple, 250, true);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1250.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1500.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1750.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2250.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2500.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2750.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

}

void reamber_base_test::lib_create_copies_reldiff() {
    auto copies = amber_f::copy_rel(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 0.25, false);

    std::vector<std::string> expected = {
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies->get_string_raw_v() == expected);

    copies = amber_f::copy_rel(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 0.25, true);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies->get_string_raw_v() == expected);
}

void reamber_base_test::lib_create_copies_reldiff_delay() {
    auto copies = amber_f::copy_rel<hit_object>
            (&mocks.hit_object_multiple, 0.25, false);

    std::vector<std::string> expected = {
        "64,192,1250.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2250.000000,128,0,2500.000000:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    copies = amber_f::copy_rel<hit_object>
            (&mocks.hit_object_multiple, 0.25, true);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1250.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2250.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);
}

void reamber_base_test::lib_create_copies_absdiff() {
    // EXCLUDE
    auto copies = amber_f::copy_abs(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 50, false, true, false);

    std::vector<std::string> expected = {
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // EXCLUDE
    copies = amber_f::copy_abs(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 50, true, true, false);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,150.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // EXCLUDE OVERLAP
    copies = amber_f::copy_abs(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 250, true, true, true);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav",
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // FROM THE BACK
    copies = amber_f::copy_abs(
                std::vector<double>({ 100, 300 }), mocks.hit_object_note, 50, true, false, true);

    expected = {
        "64,192,100.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,250.000000,1,0,0:0:0:50:hitsound.wav",
        "64,192,300.000000,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);
}
void reamber_base_test::lib_create_copies_absdiff_delay() {
    // EXCLUDE
    auto copies = amber_f::copy_abs<hit_object>
            (&mocks.hit_object_multiple, 15, false, true, true);

    std::vector<std::string> expected = {
        "64,192,1015.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2015.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
    };

    // INCLUDE
    QVERIFY(copies->get_string_raw_v() == expected);
    copies = amber_f::copy_abs<hit_object>
            (&mocks.hit_object_multiple, 15, true, true, true);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1015.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2015.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // EXCLUDE OVERLAP
    QVERIFY(copies->get_string_raw_v() == expected);
    copies = amber_f::copy_abs<hit_object>
            (&mocks.hit_object_multiple, 2000, true, true, true);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);

    // EXCLUDE OVERLAP
    QVERIFY(copies->get_string_raw_v() == expected);
    copies = amber_f::copy_abs<hit_object>
            (&mocks.hit_object_multiple, 100, true, false, false);

    expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "64,192,1900.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "320,192,2900.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
        "448,192,3000.000000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies->get_string_raw_v() == expected);
}
void reamber_base_test::lib_normalize() {
    auto normalized = amber_f::normalize(mocks.timing_point_multiple, 200, false);
    std::vector<std::string> expected = {
        "0.000000,-200.000000,4,1,1,50,0,0"
    };

    QVERIFY(normalized.get_string_raw_v() == expected);
}
void reamber_base_test::lib_create_stutter_relative() {
    // SV
    auto tp_v = amber_f::stutter_rel(std::vector<double>({ 100,300,700 }), 1.5, 0.25);

    std::vector<std::string> expected = {
        "100.000000,-66.666667,4,0,0,25,0,0",
        "150.000000,-120.000000,4,0,0,25,0,0",
        "300.000000,-66.666667,4,0,0,25,0,0",
        "400.000000,-120.000000,4,0,0,25,0,0",
        "700.000000,-100.000000,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);

    // BPM
    tp_v = amber_f::stutter_rel(std::vector<double>({ 100,300,700 }), 400, 0.25, 200, true, false);

    expected = {
        "100.000000,150.000000,4,0,0,25,1,0",
        "150.000000,450.000000,4,0,0,25,1,0",
        "300.000000,150.000000,4,0,0,25,1,0",
        "400.000000,450.000000,4,0,0,25,1,0",
        "700.000000,300.000000,4,0,0,25,1,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);
}
void reamber_base_test::lib_create_stutter_absolute() {
    // SV
    auto tp_v = amber_f::stutter_abs(std::vector<double>({ 100,300,700 }), 1.5, 100, 1.0);

    std::vector<std::string> expected = {
        "100.000000,-66.666667,4,0,0,25,0,0",
        "200.000000,-200.000000,4,0,0,25,0,0",
        "300.000000,-66.666667,4,0,0,25,0,0",
        "400.000000,-120.000000,4,0,0,25,0,0",
        "700.000000,-100.000000,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);

    // BPM
    tp_v = amber_f::stutter_abs(std::vector<double>({ 100,300,700 }), 150, 100, 100, true, true, true);

    expected = {
        "100.000000,400.000000,4,0,0,25,1,0",
        "200.000000,1200.000000,4,0,0,25,1,0",
        "300.000000,400.000000,4,0,0,25,1,0",
        "400.000000,720.000000,4,0,0,25,1,0",
        "700.000000,600.000000,4,0,0,25,1,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);
}

void reamber_base_test::lib_create_stutter_from_offset() {
    auto tp_v = amber_f::stutter(std::vector<double>({ 100,400,700 }), 1.5, 1.0, false, true);
    std::vector<std::string> expected = {
        "100.000000,-66.666667,4,0,0,25,0,0",
        "400.000000,-200.000000,4,0,0,25,0,0",
        "700.000000,-100.000000,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.get_string_raw_v() == expected);
}

void reamber_base_test::lib_delete_nth() {
    // HO
    auto ho_v = amber_f::delete_nth(&mocks.hit_object_multiple, 2, 1);

    std::vector<std::string> expected = {
        "64,192,1000.000000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav",
    };

    QVERIFY(ho_v->get_string_raw_v() == expected);

    // TP
    auto tp_v = amber_f::delete_nth(&mocks.timing_point_multiple, 2, 1);

    expected = {
        "0.000000,150.000000,4,1,1,50,1,0",
        "1000.000000,-50.000000,4,1,1,50,0,1"
    };

    QVERIFY(tp_v->get_string_raw_v() == expected);
}
void reamber_base_test::lib_extract_nth() {
    // HO
    auto ho_v = amber_f::extract_nth(&mocks.hit_object_multiple, 2, 1);

    std::vector<std::string> expected = {
        "320,192,2000.000000,128,0,2500.000000:0:0:0:50:hit2.wav"
    };

    QVERIFY(ho_v->get_string_raw_v() == expected);


    // TP
    auto tp_v = amber_f::extract_nth(&mocks.timing_point_multiple, 2, 1);

    expected = {
        "1000.000000,-50.000000,4,1,1,50,0,1"
    };

    QVERIFY(tp_v->get_string_raw_v() == expected);
}


QTEST_APPLESS_MAIN(reamber_base_test)

#include "tst_reamber_base_test.moc"
