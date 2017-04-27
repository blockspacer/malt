//
// Created by fatih on 4/27/17.
//

#pragma once

#include <malt/malt_fwd.hpp>
#include <utility>
#include <malt/component_mgr.hpp>

namespace malt
{
    namespace impl
    {
        template <class CompT>
        struct component_adapter
        {
            static component_mgr<CompT>& get_mgr();
        };

        template <class MsgT, class... Args> struct msg_delivery;

        template <class MsgT, class... Args>
        struct msg_delivery<MsgT(Args...)>
        {
            static void deliver(malt::entity_id id, MsgT, const Args&... args);
        };
    }
    namespace detail {
        entity_id get_id(const entity& e);
    }

    class entity
    {
        entity_id id;

        template <class T>
        friend class game;

        friend entity_id detail::get_id(const entity& e);

    public:
        entity() : id(0){}
        explicit entity(entity_id id) : id(id) {}

        template <class T>
        T* get_component()
        {
            return impl::component_adapter<T>::get_mgr().get_component(id);
        }

        template <class T>
        T* add_component()
        {
            return impl::component_adapter<T>::get_mgr().add_component(id);
        }

        template <class MsgT, class... ArgTs>
        void deliver_message(MsgT, const ArgTs&... args){
            impl::msg_delivery<MsgT(ArgTs...)>::deliver(id, MsgT{}, args...);
        }
    };

    namespace detail
    {
        inline entity_id get_id(const entity& e)
        {
            return e.id;
        }
    }
}
