/****************************************************************************
** Meta object code from reading C++ file 'QmlVideoPlayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/qml/QmlVideoPlayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QmlVideoPlayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VlcQmlVideoPlayer_t {
    QByteArrayData data[17];
    char stringdata[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VlcQmlVideoPlayer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VlcQmlVideoPlayer_t qt_meta_stringdata_VlcQmlVideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 17),
QT_MOC_LITERAL(1, 18, 13),
QT_MOC_LITERAL(2, 32, 0),
QT_MOC_LITERAL(3, 33, 12),
QT_MOC_LITERAL(4, 46, 15),
QT_MOC_LITERAL(5, 62, 22),
QT_MOC_LITERAL(6, 85, 5),
QT_MOC_LITERAL(7, 91, 4),
QT_MOC_LITERAL(8, 96, 4),
QT_MOC_LITERAL(9, 101, 6),
QT_MOC_LITERAL(10, 108, 11),
QT_MOC_LITERAL(11, 120, 9),
QT_MOC_LITERAL(12, 130, 13),
QT_MOC_LITERAL(13, 144, 3),
QT_MOC_LITERAL(14, 148, 8),
QT_MOC_LITERAL(15, 157, 5),
QT_MOC_LITERAL(16, 163, 8)
    },
    "VlcQmlVideoPlayer\0volumeChanged\0\0"
    "stateChanged\0seekableChanged\0"
    "seekableChangedPrivate\0pause\0play\0"
    "stop\0volume\0aspectRatio\0cropRatio\0"
    "deinterlacing\0url\0autoplay\0state\0"
    "seekable"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VlcQmlVideoPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       8,   58, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x02 /* Public */,
       7,    0,   56,    2, 0x02 /* Public */,
       8,    0,   57,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::Int, 0x00495103,
      10, QMetaType::Int, 0x00095103,
      11, QMetaType::Int, 0x00095103,
      12, QMetaType::Int, 0x00095103,
      13, QMetaType::QUrl, 0x00095103,
      14, QMetaType::Bool, 0x00095103,
      15, QMetaType::Int, 0x00495001,
      16, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       1,
       2,

       0        // eod
};

void VlcQmlVideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VlcQmlVideoPlayer *_t = static_cast<VlcQmlVideoPlayer *>(_o);
        switch (_id) {
        case 0: _t->volumeChanged(); break;
        case 1: _t->stateChanged(); break;
        case 2: _t->seekableChanged(); break;
        case 3: _t->seekableChangedPrivate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->pause(); break;
        case 5: _t->play(); break;
        case 6: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VlcQmlVideoPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcQmlVideoPlayer::volumeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (VlcQmlVideoPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcQmlVideoPlayer::stateChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (VlcQmlVideoPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VlcQmlVideoPlayer::seekableChanged)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject VlcQmlVideoPlayer::staticMetaObject = {
    { &VlcQmlVideoObject::staticMetaObject, qt_meta_stringdata_VlcQmlVideoPlayer.data,
      qt_meta_data_VlcQmlVideoPlayer,  qt_static_metacall, 0, 0}
};


const QMetaObject *VlcQmlVideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VlcQmlVideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VlcQmlVideoPlayer.stringdata))
        return static_cast<void*>(const_cast< VlcQmlVideoPlayer*>(this));
    return VlcQmlVideoObject::qt_metacast(_clname);
}

int VlcQmlVideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VlcQmlVideoObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = volume(); break;
        case 1: *reinterpret_cast< int*>(_v) = aspectRatio(); break;
        case 2: *reinterpret_cast< int*>(_v) = cropRatio(); break;
        case 3: *reinterpret_cast< int*>(_v) = deinterlacing(); break;
        case 4: *reinterpret_cast< QUrl*>(_v) = url(); break;
        case 5: *reinterpret_cast< bool*>(_v) = autoplay(); break;
        case 6: *reinterpret_cast< int*>(_v) = state(); break;
        case 7: *reinterpret_cast< bool*>(_v) = seekable(); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setVolume(*reinterpret_cast< int*>(_v)); break;
        case 1: setAspectRatio(*reinterpret_cast< int*>(_v)); break;
        case 2: setCropRatio(*reinterpret_cast< int*>(_v)); break;
        case 3: setDeinterlacing(*reinterpret_cast< int*>(_v)); break;
        case 4: setUrl(*reinterpret_cast< QUrl*>(_v)); break;
        case 5: setAutoplay(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void VlcQmlVideoPlayer::volumeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void VlcQmlVideoPlayer::stateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void VlcQmlVideoPlayer::seekableChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
