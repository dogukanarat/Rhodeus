#ifndef INCLUDED_RHODEUS_ABSTRACT_COMPONENT_HPP
#define INCLUDED_RHODEUS_ABSTRACT_COMPONENT_HPP

#include <string>
#include "rhodeus/Common.hpp"

namespace Rhodeus
{
    extern int InstalledComponentAddrStart __asm("section$start$__DATA$__MYSECTION");
    extern int InstalledComponentAddrStop  __asm("section$end$__DATA$__MYSECTION");
    extern int InstalledComponentInitializerStart __asm("section$start$__DATA$__MYINITIALIZER");
    extern int InstalledComponentInitializerStop  __asm("section$end$__DATA$__MYINITIALIZER");

    class AbstractComponent
    {
    public:
        AbstractComponent(std::string name);
        virtual ~AbstractComponent();

        std::string name() const { return m_name; }

        virtual int32_t initialize() = 0;
        virtual int32_t finalize() = 0;

    protected:
        void emit(const std::string& signalName);

    private:
        std::string m_name;
    };

    class ComponentManager
    {
    public:
        static ComponentManager& getInstance()
        {
            static ComponentManager instance;
            return instance;
        }

        void registerComponent(AbstractComponent* component);
        void deregisterComponent(AbstractComponent* component);

    protected:
        ComponentManager() {}
        ComponentManager(ComponentManager const&) = delete;
        void operator=(ComponentManager const&) = delete;

    private:
        std::vector<AbstractComponent*> m_components;
    };
}

#define INSTALL_COMPONENT_ASSIGN    __attribute__ ((used, section ("__DATA,__RHCOMPS")))
#define INSTALL_COMPONENT_INITIALIZER_ASSIGN __attribute__ ((used, section ("__DATA,__RHINIT")))
#define INSTALL_COMPONENT(c) static AbstractComponent* component INSTALL_COMPONENT_ASSIGN = &c
#define INSTALL_COMPONENT_INITIALIZER(i) static void(*initializer)(void) INSTALL_COMPONENT_INITIALIZER_ASSIGN = &i

#endif // INCLUDED_RHODEUS_ABSTRACT_COMPONENT_HPP
