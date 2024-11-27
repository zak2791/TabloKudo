#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

namespace QmlCacheGeneratedCode {
namespace _0x5f__ChoosingNames_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__SliderNames_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__DelegateSide_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__SliderNamesNext_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__TableChoosingNames_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__TableSide_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__TableAllSportsmens_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__ChoosingNames_en_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/ChoosingNames.qml"), &QmlCacheGeneratedCode::_0x5f__ChoosingNames_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/SliderNames.qml"), &QmlCacheGeneratedCode::_0x5f__SliderNames_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/DelegateSide.qml"), &QmlCacheGeneratedCode::_0x5f__DelegateSide_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/SliderNamesNext.qml"), &QmlCacheGeneratedCode::_0x5f__SliderNamesNext_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/TableChoosingNames.qml"), &QmlCacheGeneratedCode::_0x5f__TableChoosingNames_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/TableSide.qml"), &QmlCacheGeneratedCode::_0x5f__TableSide_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/TableAllSportsmens.qml"), &QmlCacheGeneratedCode::_0x5f__TableAllSportsmens_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/ChoosingNames_en.qml"), &QmlCacheGeneratedCode::_0x5f__ChoosingNames_en_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_resources)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(resources_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_resources))
int QT_MANGLE_NAMESPACE(qCleanupResources_resources)() {
    Q_CLEANUP_RESOURCE(resources_qmlcache);
    return 1;
}
