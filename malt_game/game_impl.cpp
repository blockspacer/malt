/*
 * DO NOT EDIT MANUALLY
 */

#include <malt/game.cpp>
#include <malt_game/game_impl.hpp>

#include <sample/sample_module.hpp>

#include <sample/components/test.hpp>
#include <sample/components/simple.hpp>

#include <malt_basic/basic_module.hpp>
#include <malt_basic/components/transform.hpp>

MALT_IMPLEMENT_GAME(game_config)

malt::game<game_config> g;
namespace malt
{
    namespace impl
    {
        template <class MsgT, class... Args>
        void msg_delivery<MsgT(Args...)>::deliver(malt::entity_id id, MsgT, const Args&... args)
        {
            g.deliver(id, MsgT{}, args...);
        };

        template <class CompT>
        component_mgr<CompT>& component_adapter<CompT>::get_mgr()
        {
            return g.get_mgr<CompT>();
        }

        template struct msg_delivery<int()>;
        template struct msg_delivery<int(int)>;
        template struct msg_delivery<render(float)>;
        template struct msg_delivery<render(float, double)>;

        template struct component_adapter<simple>;
        template struct component_adapter<test_component>;

        template struct component_adapter<transform>;
    }
}

