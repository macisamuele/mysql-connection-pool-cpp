AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libmysql-connection-pool.la

libmysql_connection_pool_la_LDFLAGS = -version-info 1:0:0

libmysql_connection_pool_la_SOURCES =       \
    logger/StderrLogger.cpp                 \
    mysql/MySqlConnection.cpp               \
    mysql/MySqlInterface.cpp                \
    resource/ResourcePool.cpp               \
    MemoryTracer.cpp

nobase_include_HEADERS =                    \
    cache/Cache.h                           \
    cache/LruCache.h                        \
    logger/StderrLogger.h                   \
    logger/Logger.h                         \
    mysql/MySqlConfig.h                     \
    mysql/MySqlConnection.h                 \
    mysql/MySqlInterface.h                  \
    resource/Resource.h                     \
    resource/ResourceFactory.h              \
    resource/ResourceInterface.h            \
    resource/ResourcePool.h                 \
    resource/ResourcePoolStat.h             \
    resource/ResourceUnavailable.h          \
    TypenameDefinitions.h                   \
    MemoryTracer.h

