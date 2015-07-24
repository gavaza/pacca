/****************************************************************************
** Meta object code from reading C++ file 'WidgetVolumeSlider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/widgets/WidgetVolumeSlider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WidgetVolumeSlider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcWidgetVolumeSlider_t {
    QByteArrayData data[13];
    char stringdata[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcWidgetVolumeSlider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcWidgetVolumeSlider_t qt_meta_stringdata_VlcWidgetVolumeSlider = {
    {
QT_MOC_LITERAL(0, 0, 21),
QT_MOC_LITERAL(1, 22, 9),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 4),
QT_MOC_LITERAL(4, 38, 7),
QT_MOC_LITERAL(5, 46, 7),
QT_MOC_LITERAL(6, 54, 9),
QT_MOC_LITERAL(7, 64, 6),
QT_MOC_LITERAL(8, 71, 13),
QT_MOC_LITERAL(9, 85, 2),
QT_MOC_LITERAL(10, 88, 10),
QT_MOC_LITERAL(11, 99, 8),
QT_MOC_LITERAL(12, 108, 12)
    },
    "VlcWidgetVolumeSlider\0newVolume\0\0mute\0"
    "setMute\0enabled\0setVolume\0volume\0"
    "volumeControl\0up\0volumeDown\0volumeUp\0"
    "updateVolume"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcWidgetVolumeSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   62,    2, 0x0a /* Public */,
       4,    1,   63,    2, 0x0a /* Public */,
       6,    1,   66,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    1,   70,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VlcWidgetVolumeSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcWidgetVolumeSlider *_t = static_cast<VlcWidgetVolumeSlider *>(_o);
        switch (_id) {
        case 0: _t->newVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: { bool _r = _t->mute();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->setMute((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->volume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: _t->volumeControl((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->volumeDown(); break;
        case 7: _t->volumeUp(); break;
        case 8: _t->updateVolume(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcWidgetVolumeSlider::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcWidgetVolumeSlider::newVolume)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject VlcWidgetVolumeSlider::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_VlcWidgetVolumeSlider.data,
      qt_meta_data_VlcWidgetVolumeSlider,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcWidgetVolumeSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcWidgetVolumeSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcWidgetVolumeSlider.stringdata))
        return static_cast<void*>(const_cast< VlcWidgetVolumeSlider*>(this));
    return QSlider::qt_metacast(_clname);
}

int VlcWidgetVolumeSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void VlcWidgetVolumeSlider::newVolume(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
