#pragma once
#include<array>
#include<vector>
#include<QString>

struct Skill
{
        QString name;
        int sp;
};

struct ArmorInfo
{
        std::array<Skill, 3> skills;
        QString name;
        int battleType;
        int slot;

};
