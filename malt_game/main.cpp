#include <iostream>
#include <malt/entity.hpp>
#include <malt/component_mgr.hpp>
#include <malt/component.hpp>

#include <sample/components/test.hpp>
#include <sample/components/simple.hpp>
#include <malt_basic/components/transform.hpp>

#include <rtk/gl/mesh.hpp>
#include <chrono>
#include <malt_render/messages.hpp>
#include <malt_render/components/mesh_renderer.hpp>
#include <malt_render/components/material.hpp>
#include <malt/message.hpp>
#include <malt_render/render_global.hpp>
#include <malt_render/components/render_test.h>

#include <malt_basic/input.hpp>
#include <malt_render/components/lights/directional_light.hpp>

static std::chrono::milliseconds dt;

namespace malt
{
namespace time
{
    std::chrono::milliseconds get_delta_time()
    {
        return dt;
    }
}
}

int main()
{
    using namespace std::chrono_literals;
    render_mod mod;
    mod.init();

    malt::entity e = malt::create_entity();

    auto light = malt::create_entity();
    light.add_component<malt::transform>();
    light.add_component<directional_light>();

    auto t = e.add_component<malt::transform>();
    t->set_scale({0.25f, 0.25f, 0.25f});

    e.add_component<render_test>();

    using clock = std::chrono::high_resolution_clock;

    auto b = clock::now();
    auto prev_frame = clock::now() - 16ms;

    int f = 0;
    while (!malt::is_terminated())
    {
        dt = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - prev_frame);
        prev_frame = clock::now();
        malt::broadcast(malt::update{});
        mod.update();
        malt::impl::post_frame();
        f++;
    }

    mod.destruct();

    std::cout << float(f) / (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - b).count() / 1000.f)  << '\n';

    return 0;
}
