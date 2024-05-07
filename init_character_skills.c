#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct_definitions.h"

int main(){
    // Character skills (player will choose 4):
    // Shadowblade strike 
    Skill *shadow_blade = (Skill*)malloc(sizeof(Skill));
    strcpy(shadow_blade->name, "Shadowblade strike");
    strcpy(shadow_blade->description, "Slash the enemy with a magical sword, reducing their health "
    "points by your attack points*1.5. Can be used without limit in a battle.");
    shadow_blade->type = 1; // direct attack
    shadow_blade->modifier[0] = NULL; // HP is unchanged
    shadow_blade->modifier[1] = 1.5; // ATK = ATK*1.5
    shadow_blade->modifier[2] =  NULL; // DEF is unchanged
    shadow_blade->duration_turn = 1; // modifies ATK points for only that turn

    // Energy barrier
    Skill *energy_barrier = (Skill*)malloc(sizeof(Skill));
    strcpy(energy_barrier->name, "Energy barrier");
    strcpy(energy_barrier->description, "Invoke a shield of energy around you which minimizes the "
    "impact of the enemy's next attack by doubling your DEF points that round. Can be used without "
    "limit in a battle");
    energy_barrier->type = 0; // temporal modifier
    energy_barrier->modifier[0] = NULL; // HP is unchanged
    energy_barrier->modifier[1] = NULL; // ATK is unchanged
    energy_barrier->modifier[2] =  2; // DEF is DEF*2
    energy_barrier->duration_turn = 1; // modifies DEF points for only that turn

    // Health exchange
    Skill *health_exchange = (Skill*)malloc(sizeof(Skill));
    strcpy(health_exchange->name, "Health Exchange");
    strcpy(health_exchange->description, "If your health points are dangerously low and you think your enemy "
    "is healthier, use this to swap your health points with theirs. This can only be used once in a battle");
    health_exchange->type = 0; // temporal modifier 
    health_exchange->modifier[0] = NULL; // character HP will be swapped with enemy HP, but there is no multiplier
    health_exchange->modifier[1] = NULL; // ATK is unchanged
    health_exchange->modifier[2] =  NULL; // DEF is unchanged
    health_exchange->duration_turn = 1; // swaps the HPs only in that round
}