#include <QtTest>

// add necessary includes here
#include <iostream>
#include <vector>
#include <algorithm/algorithm.h>
#include <object/singular/hitobject.h>
#include <object/singular/timingpoint.h>
#include <QDebug>
#include <QSharedPointer>

class TestObjs {
public:
    TestObjs() {

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
    void trimEHO();
    void HORawLoading();
    void TPRawLoad();
    void HOEditorLoading();
    void HOVRawLoading();
    void TPVRawLoading();
    void HOVEditorLoading();

    void foboHO();
    void foboTP();
    void loboHO();
    void loboTP();

    void getColumnV();
    void getOffsetMinHO();
    void getOffsetMaxHO();
    void getOffsetMinTP();
    void getOffsetMaxTP();

    void sortByOffsetHO();
    void sortByOffsetTP();

    void TPVMultiply();
    void TPVGetAve();

    void TPVArithmetic();

    void libOffsetDiff();
    void libCopySingularHO();
    void libCopyMultipleHO();
    void libCopySingularTP();
    void libCopyMultipleTP();
    void libCopySubByHO();
    void libCopySubByHODelay();
    void libCopySubToHO();
    void libCopySubToHODelay();
    void libCopyReldiff();
    void libCopyReldiffDelay();
    void libCopyAbsdiff();
    void libCopyAbsdiffDelay();
    void libNormalize();
    void libCreateStutterRelative();
    void libCreateStutterAbsolute();
    void libCreateStutterFromOffset();
    void libExtractNth();
    void libDeleteNth();

private:
    TestObjs tests = TestObjs();

};

void reamber_base_test::trimEHO() {

    QString str = tests.eHOStrMultiple;
    HitObject::trimEditorHitObject(str);
    QVERIFY(QString("1000|1,2000|2") == str);
}
void reamber_base_test::HORawLoading()
{
    HitObject ho;
    ho.loadRawHitObject(tests.rawHOStrNote, 4);

    QVERIFY(ho == tests.hoNote);
}
void reamber_base_test::TPRawLoad()
{
    TimingPoint tp;
    tp.loadRawTimingPoint(tests.rawTPBpm);

    QVERIFY(tp == tests.tpBpm);
}
void reamber_base_test::HOEditorLoading()
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

void reamber_base_test::HOVRawLoading() {
    HitObjectV ho_v;
    ho_v.loadRawHitObject(tests.rawHOStrMultiple, 4);

    QVERIFY(ho_v == tests.hoMultiple);
}
void reamber_base_test::TPVRawLoading() {
    TimingPointV tpV;
    tpV.loadRawTimingPoint(tests.rawTPStrMultiple);

    QVERIFY(tpV == tests.tpMultiple);
}
void reamber_base_test::HOVEditorLoading() {
    HitObjectV ho_v;
    ho_v.loadEditorHitObject(tests.eHOStrMultiple, 4);

    QVERIFY(ho_v == tests.eHOMutliple);
}

// FOBO: First Object By Offset
// LOBO: Last  Object By Offset
void reamber_base_test::foboHO()
{
    QVERIFY(
                tests.hoMultiple[0] == // Expect the first object
            tests.hoMultiple.getFirstObjectByOffset()
            );
}
void reamber_base_test::foboTP()
{
    QVERIFY(
                tests.tpMultiple[0] == // Expect the first object
            tests.tpMultiple.getFirstObjectByOffset()
            );
}
void reamber_base_test::loboHO()
{
    QVERIFY(
                tests.hoMultiple[2] == // Expect the first object
            tests.hoMultiple.getLastObjectByOffset()
            );
}
void reamber_base_test::loboTP()
{
    QVERIFY(
                tests.tpMultiple[2] == // Expect the first object
            tests.tpMultiple.getLastObjectByOffset()
            );
}

void reamber_base_test::getColumnV() {
    QVERIFY((tests.hoMultiple.getColumnV() ==
            QVector<unsigned int>{0, 2, 3}));
}
void reamber_base_test::getOffsetMinHO() {
    QVERIFY(tests.hoMultiple.getOffsetMin() == 1000.0);
}
void reamber_base_test::getOffsetMaxHO() {
    QVERIFY(tests.hoMultiple.getOffsetMax() == 3000.0);
}
void reamber_base_test::getOffsetMinTP() {
    QVERIFY(tests.tpMultiple.getOffsetMin() == 0.0);
}
void reamber_base_test::getOffsetMaxTP() {
    QVERIFY(tests.tpMultiple.getOffsetMax() == 2000.0);
}

void reamber_base_test::sortByOffsetHO() {
    HitObjectV ho_v = tests.hoMultiple;

    // Manually sort by descending
    HitObjectV ho_v_sort_desc = HitObjectV(3);
    ho_v_sort_desc[0] = ho_v[2];
    ho_v_sort_desc[1] = ho_v[1];
    ho_v_sort_desc[2] = ho_v[0];

    // Sort by Descending
    ho_v.sortByOffset(false);

    QVERIFY(ho_v == ho_v_sort_desc);
}
void reamber_base_test::sortByOffsetTP() {
    TimingPointV tpV = tests.tpMultiple;

    // Manually sort by descending
    TimingPointV tpVSortDesc = TimingPointV(3);
    tpVSortDesc[0] = tpV[2];
    tpVSortDesc[1] = tpV[1];
    tpVSortDesc[2] = tpV[0];

    // Sort by Descending
    tpV.sortByOffset(false);

    QVERIFY(tpV == tpVSortDesc);
}

void reamber_base_test::TPVMultiply() {
    //        [0] [1] [2] [3] [4]
    // SELF :  1   1           1
    // EFF  :  1       1   1
    TimingPointV tpV(4);

    tpV[0].loadParameters(0, 1, false);
    tpV[1].loadParameters(1, 2, false);
    tpV[2].loadParameters(4, 4, false);
    tpV[3].loadParameters(5, 8, false);
    TimingPointV tpV_eff(3);

    tpV_eff[0].loadParameters(0, 1, false);
    tpV_eff[1].loadParameters(2, 0.5, false);
    tpV_eff[2].loadParameters(3, 0.25, false);

    tpV.crossEffectMultiply(tpV_eff);

    QVector<QString> expected = {
        "0,-100,4,0,0,25,0,0",
        "1,-50,4,0,0,25,0,0",
        "4,-100,4,0,0,25,0,0",
        "5,-50,4,0,0,25,0,0"
    };

    QVERIFY(tpV.getStringRawV() == expected);
}
void reamber_base_test::TPVGetAve() {
    // SV
    TimingPointV tpV = TimingPointV(3);
    tpV[0].loadParameters(0, 1.5, false);
    tpV[1].loadParameters(100, 0.5, false);
    tpV[2].loadParameters(400, 1.75, false);

    QVERIFY(0.75 == tpV.getAverageSvValue());

    // BPM
    tpV = TimingPointV(3);
    tpV[0].loadParameters(0, 200, true);
    tpV[1].loadParameters(100, 100, true);
    tpV[2].loadParameters(400, 150, true);

    QVERIFY(125.0 == tpV.getAverageBpmValue());

    // MIXED
    tpV = TimingPointV(4);
    tpV[0].loadParameters(0, 200, true);
    tpV[1].loadParameters(50, 0.5, false); // JUNK SV
    tpV[2].loadParameters(100, 100, true);
    tpV[3].loadParameters(400, 150, true);

    QVERIFY(125.0 == tpV.getAverageBpmValue());
}

void reamber_base_test::TPVArithmetic()
{
    // +
    TimingPointV tpV = TimingPointV(3);
    tpV[0].loadParameters(0, 1.5, false);
    tpV[1].loadParameters(100, 0.5, false);
    tpV[2].loadParameters(400, 1.75, false);

    tpV += 2;

    for (auto tp : tpV) {
        qDebug() << tp.getStringRaw().toStdString().c_str();
    }

    QVERIFY(true);
}

void reamber_base_test::libOffsetDiff() {
    auto offsetDifference = algorithm::offsetDiff<HitObject>(tests.pHOMultiple);
    QVERIFY(offsetDifference == QVector<double>({1000, 1000}));
}
void reamber_base_test::libCopySingularHO() {
    auto copies = algorithm::copy<HitObject>(tests.hoNote, QVector<double>{1000, 2000});
    QVERIFY(QVector<double>({ 1000,2000 }) == copies.getOffsetV(false));
}
void reamber_base_test::libCopyMultipleHO() {
    auto copies = algorithm::copy<HitObject>(tests.pHOMultiple, QVector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(QVector<double>({ 1000,2000,3000,4000 }) == copies.getOffsetV(true));
}
void reamber_base_test::libCopySingularTP() {
    auto copies = algorithm::copy<TimingPoint>(tests.tpSv, QVector<double>{1000, 2000});
    QVERIFY(QVector<double>({ 1000,2000 }) == copies.getOffsetV(false));
}
void reamber_base_test::libCopyMultipleTP() {
    auto copies = algorithm::copy<TimingPoint>(tests.pTPMultiple, QVector<double>{1000, 2000});
    // Get unique offset for copies
    QVERIFY(QVector<double>({ 1000,2000,3000,4000 }) == copies.getOffsetV(true));
}
void reamber_base_test::libCopySubByHO() {
    // EXCLUDE
    auto copies = algorithm::copySubdBy<HitObject>
            (QVector<double>({ 100,400,700 }), tests.hoNote, 2, false);

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
            (QVector<double>({ 100,400,700 }), tests.hoNote, 2, true);

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
void reamber_base_test::libCopySubByHODelay() {
    auto copies = algorithm::copySubdBy<HitObject>(tests.pHOMultiple, 4, false);

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

    copies = algorithm::copySubdBy<HitObject>(tests.pHOMultiple, 4, true);

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
void reamber_base_test::libCopySubToHO() {
    // EXCLUDE
    auto copies = algorithm::copySubdTo<HitObject>
            (QVector<double>({ 100,300,500 }), tests.hoNote, 50, false);

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
            (QVector<double>({ 100,300,500 }), tests.hoNote, 50, true);

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
void reamber_base_test::libCopySubToHODelay() {
    auto copies = algorithm::copySubdTo<HitObject>(tests.pHOMultiple, 250, false);

    QVector<QString> expected = {
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "64,192,1500,1,0,0:0:0:40:hit1.wav",
        "64,192,1750,1,0,0:0:0:40:hit1.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2500,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2750,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copySubdTo<HitObject>(tests.pHOMultiple, 250, true);

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

void reamber_base_test::libCopyReldiff() {
    auto copies = algorithm::copyRel(
                QVector<double>({ 100, 300 }), tests.hoNote, 0.25, false);

    QVector<QString> expected = {
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copyRel(
                QVector<double>({ 100, 300 }), tests.hoNote, 0.25, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav",
    };
    QVERIFY(copies.getStringRawV() == expected);
}

void reamber_base_test::libCopyReldiffDelay() {
    auto copies = algorithm::copyRel<HitObject>
            (tests.pHOMultiple, 0.25, false);

    QVector<QString> expected = {
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    copies = algorithm::copyRel<HitObject>
            (tests.pHOMultiple, 0.25, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1250,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2250,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}

void reamber_base_test::libCopyAbsdiff() {
    // EXCLUDE
    auto copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), tests.hoNote, 50, false, true, false);

    QVector<QString> expected = {
        "64,192,150,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), tests.hoNote, 50, true, true, false);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,150,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE OVERLAP
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), tests.hoNote, 250, true, true, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav",
    };

    QVERIFY(copies.getStringRawV() == expected);

    // FROM THE BACK
    copies = algorithm::copyAbs(
                QVector<double>({ 100, 300 }), tests.hoNote, 50, true, false, true);

    expected = {
        "64,192,100,1,0,0:0:0:50:hitsound.wav",
        "64,192,250,1,0,0:0:0:50:hitsound.wav",
        "64,192,300,1,0,0:0:0:50:hitsound.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::libCopyAbsdiffDelay() {
    // EXCLUDE
    auto copies = algorithm::copyAbs<HitObject>
            (tests.pHOMultiple, 15, false, true, true);

    QVector<QString> expected = {
        "64,192,1015,1,0,0:0:0:40:hit1.wav",
        "320,192,2015,128,0,2500:0:0:0:50:hit2.wav",
    };

    // INCLUDE
    QVERIFY(copies.getStringRawV() == expected);
    copies = algorithm::copyAbs<HitObject>
            (tests.pHOMultiple, 15, true, true, true);

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
            (tests.pHOMultiple, 2000, true, true, true);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);

    // EXCLUDE OVERLAP
    QVERIFY(copies.getStringRawV() == expected);
    copies = algorithm::copyAbs<HitObject>
            (tests.pHOMultiple, 100, true, false, false);

    expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "64,192,1900,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
        "320,192,2900,128,0,2500:0:0:0:50:hit2.wav",
        "448,192,3000,1,0,0:0:0:60:hit3.wav"
    };

    QVERIFY(copies.getStringRawV() == expected);
}
void reamber_base_test::libNormalize() {
    auto normalized = algorithm::normalize(tests.tpMultiple, 200, false);
    QVector<QString> expected = {
        "0,-200,4,1,1,50,0,0"
    };

    QVERIFY(normalized.getStringRawV() == expected);
}
void reamber_base_test::libCreateStutterRelative() {
    // SV
    auto tpV = algorithm::stutterRel(QVector<double>({ 100,350,600 }), 4, 0.2);

    QVector<QString> expected = {
        "100,-25,4,0,0,25,0,0",
        "150,-400,4,0,0,25,0,0",
        "350,-25,4,0,0,25,0,0",
        "400,-400,4,0,0,25,0,0",
        "600,-100,4,0,0,25,0,0"
    };    for (auto s : tpV.getStringRawV())qDebug () << s;

    QVERIFY(tpV.getStringRawV() == expected);

    // BPM
    tpV = algorithm::stutterRel(QVector<double>({ 100,300,700 }), 400, 0.25, 200, true, false);

    expected = {
        "100,150,4,0,0,25,1,0",
        "150,450,4,0,0,25,1,0",
        "300,150,4,0,0,25,1,0",
        "400,450,4,0,0,25,1,0",
        "700,300,4,0,0,25,1,0"
    };

    QVERIFY(tpV.getStringRawV() == expected);
}
void reamber_base_test::libCreateStutterAbsolute() {
    // SV
    auto tpV = algorithm::stutterAbs(QVector<double>({ 100,300,700 }), 1.5, 100, 1.0);

    //for (auto s : tpV.getStringRawV()) qDebug () << s;

    QVector<QString> expected = {
        "100,-66.66666667,4,0,0,25,0,0",
        "200,-200,4,0,0,25,0,0",
        "300,-66.66666667,4,0,0,25,0,0",
        "400,-120,4,0,0,25,0,0",
        "700,-100,4,0,0,25,0,0"
    };

    QVERIFY(tpV.getStringRawV() == expected);

    // BPM
    tpV = algorithm::stutterAbs(QVector<double>({ 100,300,700 }), 150, 100, 100, true, true, true);

    expected = {
        "100,400,4,0,0,25,1,0",
        "200,1200,4,0,0,25,1,0",
        "300,400,4,0,0,25,1,0",
        "400,720,4,0,0,25,1,0",
        "700,600,4,0,0,25,1,0"
    };

    QVERIFY(tpV.getStringRawV() == expected);
}

void reamber_base_test::libCreateStutterFromOffset() {
    auto tpV = algorithm::stutter(QVector<double>({ 100,400,700 }), 1.5, 1.0, false, true);
    QVector<QString> expected = {
        "100,-66.66666667,4,0,0,25,0,0",
        "400,-200,4,0,0,25,0,0",
        "700,-100,4,0,0,25,0,0"
    };
    QVERIFY(tpV.getStringRawV() == expected);
}

void reamber_base_test::libDeleteNth() {
    // HO
    auto ho_v = algorithm::deleteNth<HitObject>(tests.pHOMultiple, 2, 1);

    QVector<QString> expected = {
        "64,192,1000,1,0,0:0:0:40:hit1.wav",
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav",
    };

    QVERIFY(ho_v.getStringRawV() == expected);

    // TP
    auto tpV = algorithm::deleteNth<TimingPoint>(tests.pTPMultiple, 2, 1);

    expected = {
        "0,150,4,1,1,50,1,0",
        "1000,-50,4,1,1,50,0,1"
    };

    QVERIFY(tpV.getStringRawV() == expected);
}
void reamber_base_test::libExtractNth() {
    // HO
    auto ho_v = algorithm::extractNth<HitObject>(tests.pHOMultiple, 2, 1);

    QVector<QString> expected = {
        "320,192,2000,128,0,2500:0:0:0:50:hit2.wav"
    };

    QVERIFY(ho_v.getStringRawV() == expected);


    // TP
    auto tpV = algorithm::extractNth<TimingPoint>(tests.pTPMultiple, 2, 1);

    expected = {
        "1000,-50,4,1,1,50,0,1"
    };

    QVERIFY(tpV.getStringRawV() == expected);
}


QTEST_APPLESS_MAIN(reamber_base_test)

#include "tst_reamber_base_test.moc"
