#ifndef INCLUDED_RHODEUS_APPLICATION_HPP
#define INCLUDED_RHODEUS_APPLICATION_HPP

#include <string>

#include <plog/Initializers/RollingFileInitializer.h>

#include "rhodeus/Common.hpp"
#include "rhodeus/CustomLogFormatter.hpp"
#include "rhodeus/Component.hpp"

namespace Rhodeus
{
    typedef struct _ApplicationData
    {
        std::string name;
        std::string description;
        std::string prompt;
        std::string version;
        std::string logFile;
        std::string historyFile;
        std::string configFile;
        std::string commandFile;
        uint32_t logFileMaxSize;
        uint32_t logFileMaxCount;
    } ApplicationData;

    class Application
    {
    private:
        const static ApplicationData Data;

    public:
        static Application& getInstance();

        int32_t run(int32_t argc, char** argv);
        static void signalHandler(int32_t signum);

        const ApplicationData& data() const { return const_cast<ApplicationData&>(Data); }

    protected:
        Application()
            : mIsExitRequested{false}
        {}
        Application(Application const&) = delete;
        void operator=(Application const&) = delete;

        int32_t initializeFirstStage();
        int32_t initializeSecondStage();
        int32_t initializeLoggers();
        int32_t initializeCommands();
        void registerSignalHandlers();

    private:
        bool mIsExitRequested;
        std::string mDataFolder;
        std::string mConfigurationFile;
        std::string mHistoryFile;
    };
}

#endif
