/****************************************************************************
** Meta object code from reading C++ file 'demodulation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../demodulation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'demodulation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Demodulation_t {
    QByteArrayData data[14];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Demodulation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Demodulation_t qt_meta_stringdata_Demodulation = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Demodulation"
QT_MOC_LITERAL(1, 13, 27), // "processedAmplitudeDataReady"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 15), // "QVector<double>"
QT_MOC_LITERAL(4, 58, 13), // "processedData"
QT_MOC_LITERAL(5, 72, 22), // "faultPositionsDetected"
QT_MOC_LITERAL(6, 95, 12), // "QVector<int>"
QT_MOC_LITERAL(7, 108, 14), // "faultPositions"
QT_MOC_LITERAL(8, 123, 19), // "phasePhaseDataReady"
QT_MOC_LITERAL(9, 143, 6), // "phases"
QT_MOC_LITERAL(10, 150, 11), // "receiveData"
QT_MOC_LITERAL(11, 162, 14), // "const uint8_t*"
QT_MOC_LITERAL(12, 177, 4), // "data"
QT_MOC_LITERAL(13, 182, 6) // "length"

    },
    "Demodulation\0processedAmplitudeDataReady\0"
    "\0QVector<double>\0processedData\0"
    "faultPositionsDetected\0QVector<int>\0"
    "faultPositions\0phasePhaseDataReady\0"
    "phases\0receiveData\0const uint8_t*\0"
    "data\0length"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Demodulation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int,   12,   13,

       0        // eod
};

void Demodulation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Demodulation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->processedAmplitudeDataReady((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 1: _t->faultPositionsDetected((*reinterpret_cast< const QVector<int>(*)>(_a[1]))); break;
        case 2: _t->phasePhaseDataReady((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 3: _t->receiveData((*reinterpret_cast< const uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Demodulation::*)(const QVector<double> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Demodulation::processedAmplitudeDataReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Demodulation::*)(const QVector<int> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Demodulation::faultPositionsDetected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Demodulation::*)(const QVector<double> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Demodulation::phasePhaseDataReady)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Demodulation::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_Demodulation.data,
    qt_meta_data_Demodulation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Demodulation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Demodulation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Demodulation.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int Demodulation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Demodulation::processedAmplitudeDataReady(const QVector<double> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Demodulation::faultPositionsDetected(const QVector<int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Demodulation::phasePhaseDataReady(const QVector<double> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
