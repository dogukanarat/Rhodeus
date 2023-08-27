#ifndef INCLUDED_RHODEUS_APPLICATION_HPP
#define INCLUDED_RHODEUS_APPLICATION_HPP

#include <string>
#include <plog/Initializers/RollingFileInitializer.h>
#include "rhodeus/Common.hpp"
#include "rhodeus/CustomLogFormatter.hpp"
#include "rhodeus/AbstractComponent.hpp"

namespace Rhodeus
{
    typedef struct _ApplicationData
    {
        std::string name;
        std::string description;
        std::string version;
        std::string logFile;
        std::string configFile;
        std::string commandFile;
        uint32_t logFileMaxSize;
        uint32_t logFileMaxCount;
    } ApplicationData;

    class Application
    {
    public:
        static Application& getInstance()
        {
            static Application instance;
            return instance;
        }

        int32_t run(int32_t argc, char** argv);
        static void signalHandler(int32_t signum);

        const ApplicationData& data() const { return const_cast<ApplicationData&>(Data); }

    protected:
        Application() {}
        Application(Application const&) = delete;
        void operator=(Application const&) = delete;

        void initializeDataFolder();
        void initializeLoggers();
        void registerSignalHandlers();

    private:
        const static ApplicationData Data;
        static std::string DataFolder;
        uint8_t m_isExitRequested;
        static std::vector<AbstractComponent*> m_components;
    };
}

#endif
