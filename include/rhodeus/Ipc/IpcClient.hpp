#ifndef INCLUDED_RHODEUS_IPC_CLIENT_HPP
#define INCLUDED_RHODEUS_IPC_CLIENT_HPP

#include <thread>
#include "rhodeus/Ipc/Ipc.hpp"

namespace Rhodeus
{
    class IpcClient : public IpcEndPoint
    {
    public:
        static IpcClient& getInstance();

        IpcClient& setName(const std::string& name) { mEndPointName = name; return *this; }
        IpcClient& setId(uint32_t id) { mEndPointId = id; return *this; }

        int32_t initialize() override;
        int32_t finalize() override;

    protected:
        IpcClient() : IpcEndPoint("IpcClient")
            ,mThread{nullptr}
            ,mIsExitRequested{false}
        {}
        IpcClient(IpcClient const&) = delete;
        void operator=(IpcClient const&) = delete;
        ~IpcClient() {}

        static void task(IpcClient *client);

    private:
        std::thread* mThread;
        bool mIsExitRequested;

    };
}

#endif // INCLUDED_RHODEUS_IPC_CLIENT_HPP
