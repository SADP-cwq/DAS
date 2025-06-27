/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[21];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 11), // "ReceiveData"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "const uint8_t*"
QT_MOC_LITERAL(4, 35, 4), // "data"
QT_MOC_LITERAL(5, 40, 4), // "size"
QT_MOC_LITERAL(6, 45, 20), // "ReceiveAmplitudeData"
QT_MOC_LITERAL(7, 66, 15), // "QVector<double>"
QT_MOC_LITERAL(8, 82, 9), // "amplitude"
QT_MOC_LITERAL(9, 92, 21), // "ReceiveFaultPositions"
QT_MOC_LITERAL(10, 114, 12), // "QVector<int>"
QT_MOC_LITERAL(11, 127, 9), // "positions"
QT_MOC_LITERAL(12, 137, 16), // "ReceivePhaseData"
QT_MOC_LITERAL(13, 154, 5), // "phase"
QT_MOC_LITERAL(14, 160, 20), // "on_btn_start_clicked"
QT_MOC_LITERAL(15, 181, 19), // "on_btn_stop_clicked"
QT_MOC_LITERAL(16, 201, 18), // "on_btn_ini_clicked"
QT_MOC_LITERAL(17, 220, 20), // "on_btn_close_clicked"
QT_MOC_LITERAL(18, 241, 17), // "on_btn_IQ_clicked"
QT_MOC_LITERAL(19, 259, 23), // "on_btn_IQ_close_clicked"
QT_MOC_LITERAL(20, 283, 28) // "on_btn_set_alarm_pos_clicked"

    },
    "Widget\0ReceiveData\0\0const uint8_t*\0"
    "data\0size\0ReceiveAmplitudeData\0"
    "QVector<double>\0amplitude\0"
    "ReceiveFaultPositions\0QVector<int>\0"
    "positions\0ReceivePhaseData\0phase\0"
    "on_btn_start_clicked\0on_btn_stop_clicked\0"
    "on_btn_ini_clicked\0on_btn_close_clicked\0"
    "on_btn_IQ_clicked\0on_btn_IQ_close_clicked\0"
    "on_btn_set_alarm_pos_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x08 /* Private */,
       6,    1,   74,    2, 0x08 /* Private */,
       9,    1,   77,    2, 0x08 /* Private */,
      12,    1,   80,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,
      15,    0,   84,    2, 0x08 /* Private */,
      16,    0,   85,    2, 0x08 /* Private */,
      17,    0,   86,    2, 0x08 /* Private */,
      18,    0,   87,    2, 0x08 /* Private */,
      19,    0,   88,    2, 0x08 /* Private */,
      20,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 7,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ReceiveData((*reinterpret_cast< const uint8_t*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->ReceiveAmplitudeData((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 2: _t->ReceiveFaultPositions((*reinterpret_cast< const QVector<int>(*)>(_a[1]))); break;
        case 3: _t->ReceivePhaseData((*reinterpret_cast< const QVector<double>(*)>(_a[1]))); break;
        case 4: _t->on_btn_start_clicked(); break;
        case 5: _t->on_btn_stop_clicked(); break;
        case 6: _t->on_btn_ini_clicked(); break;
        case 7: _t->on_btn_close_clicked(); break;
        case 8: _t->on_btn_IQ_clicked(); break;
        case 9: _t->on_btn_IQ_close_clicked(); break;
        case 10: _t->on_btn_set_alarm_pos_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<double> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
