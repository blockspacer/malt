//
// Created by fatih on 4/27/17.
//

#pragma once

#include <malt/component.hpp>
#include <sample/sample_module.hpp>


class simple : public malt::component
{
public:
    void Handle(render, float dt);
};

