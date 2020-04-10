#include <QtTest>

// add necessary includes here
#include <iostream>
#include <vector>
#include <algorithm/algorithm.h>
#include <object/singular/hitobject.h>
#include <object/singular/timingpoint.h>
#include <QDebug>
#include <QSharedPointer>

class mock_objects {
public:
    mock_objects() {

        hoNote.loadParameters(
            0, 192, 1000, HitObject::NORMAL, OsuObject::SAMPLE_SET::AUTO, 0,
            OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
            OsuObject::SAMPLE_SET::AUTO, 50, "hitsound.wav", 4);
        hoLongNote.loadParameters(
            0, 192, 1000, HitObject::LN, OsuObject::SAMPLE_SET::AUTO, 1500,
            OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
            OsuObject::SAMPLE_SET::AUTO, 50, "hitsound.wav", 4);

        tpSv.loadParameters(
            1000, 2, 4, OsuObject::SAMPLE_SET::AUTO, 0, 50, false, false
        );
        tpBpm.loadParameters(
            1000, 300, 4, OsuObject::SAMPLE_SET::AUTO, 0, 50, true, false
        );

        eHOSingular.loadParameters(1, 1000, 0, 4);

        eHOMutliple[0].loadParameters(1, 1000, 0, 4);
        eHOMutliple[1].loadParameters(2, 2000, 0, 4);

        hoMultiple[0].loadParameters(
            0, 192, 1000, HitObject::NORMAL, OsuObject::SAMPLE_SET::AUTO, 0,
            OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
            OsuObject::SAMPLE_SET::AUTO, 40, "hit1.wav", 4);
        hoMultiple[1].loadParameters(
            2, 192, 2000, HitObject::LN, OsuObject::SAMPLE_SET::AUTO, 2500,
            OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
            OsuObject::SAMPLE_SET::AUTO, 50, "hit2.wav", 4);
        hoMultiple[2].loadParameters(
            3, 192, 3000, HitObject::NORMAL, OsuObject::SAMPLE_SET::AUTO, 0,
            OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
            OsuObject::SAMPLE_SET::AUTO, 60, "hit3.wav", 4);

        tpMultiple[0].loadParameters(
            0, 400, 4, OsuObject::SAMPLE_SET::NORMAL, 1, 50, true, false
        );
        tpMultiple[1].loadParameters(
            1000, 2, 4, OsuObject::SAMPLE_SET::NORMAL, 1, 50, false, true
        );
        tpMultiple[2].loadParameters(
            2000, 0.5, 4, OsuObject::SAMPLE_SET::NORMAL, 1, 50, false, false
        );

        pEHOMutliple = QSPtr<HitObjectV>::create(eHOMutliple);
        pHOMultiple = QSPtr<HitObjectV>::create(hoMultiple);
        pTPMultiple = QSPtr<TimingPointV>::create(tpMultiple);

    }
    QString rawHOStrNote =
        "64,192,1000,1,0,0:0:0:50:hitsound.wav";
    QString rawHOStrLongNote =
        "64,192,1000,128,0,1500:0:0:0:50:hitsound.wav";
    QString rawTPSv =
        "1000,-50,4,0,0,50,0,0";
    QString rawTPBpm =
        "1000,200,4,0,0,50,1,0";
    QString eHOStrSingular =
        "00:01:000 (1000|1) -";
    QString eHOStrMultiple =
        "00:01:000 (1000|1,2000|2) -";

    QString rawHOStrMultiple =
        "64,192,1000,1,0,0:0:0:40:hit1.wav\n" // N
        "320,192,2000,128,0,2500:0:0:0:70:hit2.wav\n" // LN
        "448,192,3000,1,0,0:0:0:60:hit3.wav"; // N

    QString rawTPStrMultiple =
        "0,150,4,1,1,50,1,0\n" // BPM 400
        "1000,-50,4,1,1,50,0,1\n" // SV 2.0 Kiai
        "2000,-200,4,1,1,50,0,0"; // SV 0.50

    HitObject hoNote;
    HitObject hoLongNote;
    TimingPoint tpSv;
    TimingPoint tpBpm;
    HitObject eHOSingular;
    HitObjectV eHOMutliple = HitObjectV(2);
    HitObjectV hoMultiple = HitObjectV(3);
    TimingPointV tpMultiple = TimingPointV(3);

    QSPtr<HitObjectV>   pEHOMutliple;
    QSPtr<HitObjectV>   pHOMultiple ;
    QSPtr<TimingPointV> pTPMultiple ;

};

class reamber_base_test : public QObject
{
    Q_OBJECT

private slots:
    void trim_editor_HitObject();
    void HitObject_raw_loading();
    void TimingPoint_raw_load();
    void HitObject_editor_loading();
    void HitObjectV_raw_loading();
    void TimingPointV_raw_loading();
    void HitObjectV_editor_loading();

    void fobo_HitObject();
    void fobo_TimingPoint();
    void lobo_HitObject();
    void lobo_TimingPoint();

    void get_column_v();
    void get_offset_min_HitObject();
    void get_offset_max_HitObject();
    void get_offset_min_TimingPoint();
    void get_offset_max_TimingPoint();

    void sort_by_offset_HitObject();
    void sort_by_offset_TimingPoint();

    void TimingPointV_multiply();
    void TimingPointV_get_ave();

    void TimingPointV_arithmetic();

    void lib_offset_diff();
    void lib_copy_singular_HitObject();
    void lib_copy_multiple_HitObject();
    void lib_copy_singular_TimingPoint();
    void lib_copy_multiple_TimingPoint();
    void lib_copy_sub_by_HitObject();
    void lib_copy_sub_by_HitObject_delay();
    void lib_copy_sub_to_HitObject();
    void lib_copy_sub_to_HitObject_delay();
    void lib_copy_reldiff();
    void lib_copy_reldiff_delay();
    void lib_copy_absdiff();
    void lib_copy_absdiff_delay();
    void lib_normalize();
    void lib_create_stutter_relative();
    void lib_create_stutter_absolute();
    void lib_create_stutter_from_offset();
    void lib_extract_nth();
    void lib_delete_nth();

private:
    mock_objects mocks = mock_objects();

};

void reamber_base_test::trim_editor_HitObject() {

    QString str = mocks.eHOStrMultiple;
    HitObject::trimEditorHitObject(str);
    QVERIFY(QString("1000|1,2000|2") == str);
}
void reamber_base_test::HitObject_raw_loading()
{
    HitObject ho;
    ho.loadRawHitObject(mocks.rawHOStrNote, 4);

    QVERIFY(ho == mocks.hoNote);
}
void reamber_base_test::TimingPoint_raw_load()
{
    TimingPoint tp;
    tp.loadRawTimingPoint(mocks.rawTPBpm);

    QVERIFY(tp == mocks.tpBpm);
}
void reamber_base_test::HitObject_editor_loading()
{
    HitObject ho;
    QString load_str = "00:01:000 (1000|0) - ";
    ho.loadEditorHitObject(load_str, 4);

    HitObject ho_expected;
    ho_expected.loadParameters(
                0, 192, 1000, HitObject::NOTE_TYPE::NORMAL, OsuObject::SAMPLE_SET::AUTO,
                0, OsuObject::SAMPLE_SET::AUTO, OsuObject::SAMPLE_SET::AUTO,
                OsuObject::SAMPLE_SET::AUTO, 50, "", 4);

    QVERIFY(ho_expected == ho);

}

void reamber_base_test::HitObjectV_raw_loading() {
    HitObjectV ho_v;
    ho_v.loadRawHitObject(mocks.rawHOStrMultiple, 4);

    QVERIFY(ho_v == mocks.hoMultiple);
}
void reamber_base_test::TimingPointV_raw_loading() {
    TimingPointV tp_v;
    tp_v.loadRawTimingPoint(mocks.rawTPStrMultiple);

    QVERIFY(tp_v == mocks.tpMultiple);
}
void reamber_base_test::HitObjectV_editor_loading() {
    HitObjectV ho_v;
    ho_v.loadEditorHitObject(mocks.eHOStrMultiple, 4);

    QVERIFY(ho_v == mocks.eHOMutliple);
}

// FOBO: First Object By Offset
// LOBO: Last  Object By Offset
void reamber_base_test::fobo_HitObject()
{
    QVERIFY(
                mocks.hoMultiple[0] == // Expect the first object
            mocks.hoMultiple.getFirstObjectByOffset()
            );
}
void reamber_base_test::fobo_TimingPoint()
{
    QVERIFY(
                mocks.tpMultiple[0] == // Expect the first object
            mocks.tpMultiple.getFirstObjectByOffset()
            );
}
void reamber_base_test::lobo_HitObject()
{
    QVERIFY(
                mocks.hoMultiple[2] == // Expect the first object
            mocks.hoMultiple.getLastObjectByOffset()
            );
}
void reamber_base_test::lobo_TimingPoint()
{
    QVERIFY(
                mocks.tpMultiple[2] == // Expect the first object
            mocks.tpMultiple.getLastObjectByOffset()
            );
}

void reamber_base_test::get_column_v() {
    QVERIFY((mocks.hoMultiple.getColumnV() ==
            QVector<unsigned int>{0, 2, 3}));
}
void reamber_base_test::get_offset_min_HitObject() {
    QVERIFY(mocks.hoMultiple.getOffsetMin() == 1000.0);
}
void reamber_base_test::get_offset_max_HitObject() {
    QVERIFY(mocks.hoMultiple.getOffsetMax() == 3000.0);
}
void reamber_base_test::get_offset_min_TimingPoint() {
    QVERIFY(mocks.tpMultiple.getOffsetMin() == 0.0);
}
void reamber_base_test::get_offset_max_TimingPoint() {
    QVERIFY(mocks.tpMultiple.getOffsetMax() == 2000.0);
}

void reamber_base_test::sort_by_offset_HitObject() {
    HitObjectV ho_v = mocks.hoMultiple;

    // Manually sort by descending
    HitObjectV ho_v_sort_desc = HitObjectV(3);
    ho_v_sort_desc[0] = ho_v[2];
    ho_v_sort_desc[1] = ho_v[1];
    ho_v_sort_desc[2] = ho_v[0];

    // Sort by Descending
    ho_v.sortByOffset(false);

    QVERIFY(ho_v == ho_v_sort_desc);
}
void reamber_base_test::sort_by_offset_TimingPoint() {
    TimingPointV tp_v = mocks.tpMultiple;

    // Manually sort by descending
    TimingPointV tp_v_sort_desc = TimingPointV(3);
    tp_v_sort_desc[0] = tp_v[2];
    tp_v_sort_desc[1] = tp_v[1];
    tp_v_sort_desc[2] = tp_v[0];

    // Sort by Descending
    tp_v.sortByOffset(false);

    QVERIFY(tp_v == tp_v_sort_desc);
}

void reamber_base_test::TimingPointV_multiply() {
    //        [0] [1] [2] [3] [4]
    // SELF :  1   1           1
    // EFF  :  1       1   1
    TimingPointV tp_v(4);

    tp_v[0].loadParameters(0, 1, false);
    tp_v[1].loadParameters(1, 2, false);
    tp_v[2].loadParameters(4, 4, false);
    tp_v[3].loadParameters(5, 8, false);
    TimingPointV tp_v_eff(3);

    tp_v_eff[0].loadParameters(0, 1, false);
    tp_v_eff[1].loadParameters(2, 0.5, false);
    tp_v_eff[2].loadParameters(3, 0.25, false);

    tp_v.crossEffectMultiply(tp_v_eff);

    QVector<QString> expected = {
        "0,-100,4,0,0,25,0,0",
        "1,-50,4,0,0,25,0,0",
        "4,-100,4,0,0,25,0,0",
        "5,-50,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.getStringRawV() == expected);
}
void reamber_base_test::TimingPointV_get_ave() {
    // SV
    TimingPointV tp_v = TimingPointV(3);
    tp_v[0].loadParameters(0, 1.5, false);
    tp_v[1].loadParameters(100, 0.5, false);
    tp_v[2].loadParameters(400, 1.75, false);

    QVERIFY(0.75 == tp_v.getAverageSvValue());

    // BPM
    tp_v = TimingPointV(3);
    tp_v[0].loadParameters(0, 200, true);
    tp_v[1].loadParameters(100, 100, true);
    tp_v[2].loadParameters(400, 150, true);

    QVERIFY(125.0 == tp_v.getAverageBpmValue());

    // MIXED
    tp_v = TimingPointV(4);
    tp_v[0].loadParameters(0, 200, true);
    tp_v[1].loadParameters(50, 0.5, false); // JUNK SV
    tp_v[2].loadParameters(100, 100, true);
    tp_v[3].loadParameters(400, 150, true);

    QVERIFY(125.0 == tp_v.getAverageBpmValue());
}

void reamber_base_test::TimingPointV_arithmetic()
{
    // +
    TimingPointV tp_v = TimingPointV(3);
    tp_v[0].loadParameters(0, 1.5, false);
    tp_v[1].loadParameters(100, 0.5, false);
    tp_v[2].loadParameters(400, 1.75, false);

    tp_v += 2;

    for (auto tp : tp_v) {
        qDebug() << tp.getStringRaw().toStdString().c_str();
    }

    QVERIFY(true);
}

void reamber_base_test::lib_offset_diff() {
    auto offsetDifference = algorithm::offsetDiff<HitObject>(mocks.pHOMultiple);
    QVERIFY(offsetDifference == QVector<double>({1000, 1000}));
}
void reamber_base_test::lib_copy_singular_HitObject() {
    auto copies = algorithm::copy<HitObject>(mocks.hoNote, QVector<double>{1000, 2000});
    QVERIFY(QVector<double>({ 1000,2000 }) == copies.getOffsetV(false));
}
void reamber_base_test::lib_copy_multiple_HitObject() {
    auto copies = algorithm::copy<HitObject>(mocks.pHOMultiple, QVector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(QVector<double>({ 1000,2000,3000,4000 }) == copies.getOffsetV(true));
}
void reamber_base_test::lib_copy_singular_TimingPoint() {
    auto copies = algorithm::copy<TimingPoint>(mocks.tpSv, QVector<double>{1000, 2000});
    QVERIFY(QVector<double>({ 1000,2000 }) == copies.getOffsetV(false));
}
void reamber_base_test::lib_copy_multiple_TimingPoint() {
    auto copies = algorithm::copy<TimingPoint>(mocks.pTPMultiple, QVector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(QVector<double>({ 1000,2000,3000,4000 }) == copies.getOffsetV(true));
}
void reamber_base_test::lib_copy_sub_by_HitObject() {
    // EXCLUDE
    auto copies = algorithm::copySubdBy<HitObject>
            (QVector<double>({ 100,400,700 }), mocks.hoNote, 2, false);

//    for (auto s : copies.getStringRawV())
//        qDebug() << s;

    QVector<QString> expected = {
        "64,192,200,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,300,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,500,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,600,1,0,0:0:0:50:hitsound.wav" // Subd 2
    };

    QVERIFY(copies.getStringRawV() == expected);

    // INCLUDE
    copies = algorithm::copySubdBy<HitObject>
            (QVector<double>({ 100,400,700 }), mocks.hoNote, 2, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,200,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,300,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,400,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,500,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,600,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,700,1,0,0:0:0:50:hitsound.wav"  // Subd 0
    };

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::lib_copy_sub_by_HitObject_delay() {
    auto copies = algorithm::copySubdBy<HitObject>(mocks.pHOMultiple, 4, false);

    QVector<QString> expected = {
        "64,192,1200,1,0,0:0:0:40:hit1.wav",
        "64,192,1400,1,0,0:0:0:40:hit1.wav",
        "64,192,1600,1,0,0:0:0:40:hit1.wav",
        "64,192,1800,1,0,0:0:0:40:hit1.wav",
        "320,192,2200,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2400,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2600,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2800,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copySubdBy<HitObject>(mocks.pHOMultiple, 4, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1200,1,0,0:0:0:40:hit1.wav",
        "64,192,1400,1,0,0:0:0:40:hit1.wav",
        "64,192,1600,1,0,0:0:0:40:hit1.wav",
        "64,192,1800,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2200,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2400,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2600,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2800,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

}
void reamber_base_test::lib_copy_sub_to_HitObject() {
    // EXCLUDE
    auto copies = algorithm::copySubdTo<HitObject>
            (QVector<double>({ 100,300,500 }), mocks.hoNote, 50, false);

    QVector<QString> expected = {
        "64,192,150,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,200,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,250,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,350,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,400,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,450,1,0,0:0:0:50:hitsound.wav"  // Subd 3
    };

//    for (auto ho : copies) {
//        qDebug() << ho.getStringRaw().toStdString().c_str();
//    }

    QVERIFY(copies.getStringRawV() == expected);

    // INCLUDE
    copies = algorithm::copySubdTo<HitObject>
            (QVector<double>({ 100,300,500 }), mocks.hoNote, 50, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,150,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,200,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,250,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,300,1,0,0:0:0:50:hitsound.wav", // Subd 0
        "64,192,350,1,0,0:0:0:50:hitsound.wav", // Subd 1
        "64,192,400,1,0,0:0:0:50:hitsound.wav", // Subd 2
        "64,192,450,1,0,0:0:0:50:hitsound.wav", // Subd 3
        "64,192,500,1,0,0:0:0:50:hitsound.wav"  // Subd 0
    };

//    for (auto ho : copies) {
//        qDebug() << ho.getStringRaw().toStdString().c_str();
//    }

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::lib_copy_sub_to_HitObject_delay() {
    auto copies = algorithm::copySubdTo<HitObject>(mocks.pHOMultiple, 250, false);

    QVector<QString> expected = {
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "64,192,1500,1,0,0:0:0:40:hit1.wav",
        "64,192,1750,1,0,0:0:0:40:hit1.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2500,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2750,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copySubdTo<HitObject>(mocks.pHOMultiple, 250, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "64,192,1500,1,0,0:0:0:40:hit1.wav",
        "64,192,1750,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2500,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2750,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

}

void reamber_base_test::lib_copy_reldiff() {
    auto copies = algorithm::copyRel(
                QVector<double>({ 100, 300 }), mocks.hoNote, 0.25, false);

    QVector<QString> expected = {
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copyRel(
                QVector<double>({ 100, 300 }), mocks.hoNote, 0.25, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies.getStringRawV() == expected);
}

void reamber_base_test::lib_copy_reldiff_delay() {
    auto copies = algorithm::copyRel<HitObject>
            (mocks.pHOMultiple, 0.25, false);

    QVector<QString> expected = {
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copyRel<HitObject>
            (mocks.pHOMultiple, 0.25, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}

void reamber_base_test::lib_copy_absdiff() {
    // EXCLUDE
    auto copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), mocks.hoNote, 50, false, true, false);

    QVector<QString> expected = {
        "64,192,150,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), mocks.hoNote, 50, true, true, false);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE OVERLAP
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), mocks.hoNote, 250, true, true, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav",
    };

    QVERIFY(copies.getStringRawV() == expected);

    // FROM THE BACK
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), mocks.hoNote, 50, true, false, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,250,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::lib_copy_absdiff_delay() {
    // EXCLUDE
    auto copies = algorithm::copyAbs<HitObject>
            (mocks.pHOMultiple, 15, false, true, true);

    QVector<QString> expected = {
        "64,192,1015,1,0,0:0:0:40:hit1.wav",
        "320,192,2015,128,0,2500:0:0:0:50:hit2.wav",
    };

    // INCLUDE
    QVERIFY(copies.getStringRawV() == expected);
    copies = algorithm::copyAbs<HitObject>
            (mocks.pHOMultiple, 15, true, true, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1015,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2015,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE OVERLAP
    QVERIFY(copies.getStringRawV() == expected);
    copies = algorithm::copyAbs<HitObject>
            (mocks.pHOMultiple, 2000, true, true, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE OVERLAP
    QVERIFY(copies.getStringRawV() == expected);
    copies = algorithm::copyAbs<HitObject>
            (mocks.pHOMultiple, 100, true, false, false);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1900,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2900,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::lib_normalize() {
    auto normalized = algorithm::normalize(mocks.tpMultiple, 200, false);
    QVector<QString> expected = {
        "0,-200,4,1,1,50,0,0"
    };

    QVERIFY(normalized.getStringRawV() == expected);
}
void reamber_base_test::lib_create_stutter_relative() {
    // SV
    auto tp_v = algorithm::stutterRel(QVector<double>({ 100,350,600 }), 4, 0.2);

    QVector<QString> expected = {
        "100,-25,4,0,0,25,0,0",
        "150,-400,4,0,0,25,0,0",
        "350,-25,4,0,0,25,0,0",
        "400,-400,4,0,0,25,0,0",
        "600,-100,4,0,0,25,0,0"
    };    for (auto s : tp_v.getStringRawV())qDebug () << s;

    QVERIFY(tp_v.getStringRawV() == expected);

    // BPM
    tp_v = algorithm::stutterRel(QVector<double>({ 100,300,700 }), 400, 0.25, 200, true, false);

    expected = {
        "100,150,4,0,0,25,1,0",
        "150,450,4,0,0,25,1,0",
        "300,150,4,0,0,25,1,0",
        "400,450,4,0,0,25,1,0",
        "700,300,4,0,0,25,1,0"
    };

    QVERIFY(tp_v.getStringRawV() == expected);
}
void reamber_base_test::lib_create_stutter_absolute() {
    // SV
    auto tp_v = algorithm::stutterAbs(QVector<double>({ 100,300,700 }), 1.5, 100, 1.0);

    //for (auto s : tp_v.getStringRawV()) qDebug () << s;

    QVector<QString> expected = {
        "100,-66.66666667,4,0,0,25,0,0",
        "200,-200,4,0,0,25,0,0",
        "300,-66.66666667,4,0,0,25,0,0",
        "400,-120,4,0,0,25,0,0",
        "700,-100,4,0,0,25,0,0"
    };

    QVERIFY(tp_v.getStringRawV() == expected);

    // BPM
    tp_v = algorithm::stutterAbs(QVector<double>({ 100,300,700 }), 150, 100, 100, true, true, true);

    expected = {
        "100,400,4,0,0,25,1,0",
        "200,1200,4,0,0,25,1,0",
        "300,400,4,0,0,25,1,0",
        "400,720,4,0,0,25,1,0",
        "700,600,4,0,0,25,1,0"
    };

    QVERIFY(tp_v.getStringRawV() == expected);
}

void reamber_base_test::lib_create_stutter_from_offset() {
    auto tp_v = algorithm::stutter(QVector<double>({ 100,400,700 }), 1.5, 1.0, false, true);
    QVector<QString> expected = {
        "100,-66.66666667,4,0,0,25,0,0",
        "400,-200,4,0,0,25,0,0",
        "700,-100,4,0,0,25,0,0"
    };
    QVERIFY(tp_v.getStringRawV() == expected);
}

void reamber_base_test::lib_delete_nth() {
    // HO
    auto ho_v = algorithm::deleteNth<HitObject>(mocks.pHOMultiple, 2, 1);

    QVector<QString> expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
    };

    QVERIFY(ho_v.getStringRawV() == expected);

    // TP
    auto tp_v = algorithm::deleteNth<TimingPoint>(mocks.pTPMultiple, 2, 1);

    expected = {
        "0,150,4,1,1,50,1,0",
        "1000,-50,4,1,1,50,0,1"
    };

    QVERIFY(tp_v.getStringRawV() == expected);
}
void reamber_base_test::lib_extract_nth() {
    // HO
    auto ho_v = algorithm::extractNth<HitObject>(mocks.pHOMultiple, 2, 1);

    QVector<QString> expected = {
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(ho_v.getStringRawV() == expected);


    // TP
    auto tp_v = algorithm::extractNth<TimingPoint>(mocks.pTPMultiple, 2, 1);

    expected = {
        "1000,-50,4,1,1,50,0,1"
    };

    QVERIFY(tp_v.getStringRawV() == expected);
}


QTEST_APPLESS_MAIN(reamber_base_test)

#include "tst_reamber_base_test.moc"
