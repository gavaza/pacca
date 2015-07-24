/****************************************************************************
** Meta object code from reading C++ file 'Media.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/core/Media.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Media.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcMedia_t {
    QByteArrayData data[11];
    char stringdata[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcMedia_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcMedia_t qt_meta_stringdata_VlcMedia = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 11),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 9),
QT_MOC_LITERAL(4, 32, 12),
QT_MOC_LITERAL(5, 45, 15),
QT_MOC_LITERAL(6, 61, 15),
QT_MOC_LITERAL(7, 77, 13),
QT_MOC_LITERAL(8, 91, 5),
QT_MOC_LITERAL(9, 97, 12),
QT_MOC_LITERAL(10, 110, 10)
    },
    "VlcMedia\0metaChanged\0\0Vlc::Meta\0"
    "subitemAdded\0libvlc_media_t*\0"
    "durationChanged\0parsedChanged\0freed\0"
    "stateChanged\0Vlc::State"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcMedia[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       7,    1,   53,    2, 0x06 /* Public */,
       8,    1,   56,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void VlcMedia::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcMedia *_t = static_cast<VlcMedia *>(_o);
        switch (_id) {
        case 0: _t->metaChanged((*reinterpret_cast< const Vlc::Meta(*)>(_a[1]))); break;
        case 1: _t->subitemAdded((*reinterpret_cast< libvlc_media_t*(*)>(_a[1]))); break;
        case 2: _t->durationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->parsedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->freed((*reinterpret_cast< libvlc_media_t*(*)>(_a[1]))); break;
        case 5: _t->stateChanged((*reinterpret_cast< const Vlc::State(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcMedia::*_t)(const Vlc::Meta & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::metaChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (VlcMedia::*_t)(libvlc_media_t * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::subitemAdded)) {
                *result = 1;
            }
        }
        {
            typedef void (VlcMedia::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::durationChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (VlcMedia::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::parsedChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (VlcMedia::*_t)(libvlc_media_t * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::freed)) {
                *result = 4;
            }
        }
        {
            typedef void (VlcMedia::*_t)(const Vlc::State & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcMedia::stateChanged)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject VlcMedia::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VlcMedia.data,
      qt_meta_data_VlcMedia,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcMedia::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcMedia::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcMedia.stringdata))
        return static_cast<void*>(const_cast< VlcMedia*>(this));
    return QObject::qt_metacast(_clname);
}

int VlcMedia::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VlcMedia::metaChanged(const Vlc::Meta & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VlcMedia::subitemAdded(libvlc_media_t * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VlcMedia::durationChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VlcMedia::parsedChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VlcMedia::freed(libvlc_media_t * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VlcMedia::stateChanged(const Vlc::State & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
