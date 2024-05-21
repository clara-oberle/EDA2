#include <stdio.h>
#include <string.h>
#include "init_character_skills.h"

// Character skills (player will choose 4):
void init_shadowblade(Skill *shadow_blade){
    // Shadowblade 
    strcpy(shadow_blade->name, "Shadowblade strike");
    strcpy(shadow_blade->description, "Slash the enemy with a magical sword, reducing their health "
    "points by your attack points*1.5. Can be used without limit in a battle.");
    shadow_blade->type = 0; // temporary attack
    shadow_blade->modifier[0] = 1; // HP is unchanged HP = HP*1
    shadow_blade->modifier[1] = 1.5; // ATK = ATK*1.5
    shadow_blade->modifier[2] =  1; // DEF is unchanged DEF = DEF*1
    shadow_blade->duration_turn = 1; // modifies ATK points for only that turn
}

void init_frostbite(Skill *frostbite){
    // Frostbite
    strcpy(frostbite->name, "Frostbite");
    strcpy(frostbite->description, "This skill covers the battlefield in a chilling blizzard, "
    "it increases your attack points by 20 percent and decreases the enemy's defense points by 15 percent "
    "for that turn. Can be used without limit in a battle.");
    frostbite->type = 0; // temporal modifier
    frostbite->modifier[0] = 1; // HP is unchanged HP = HP*1
    frostbite->modifier[1] = 1.2; // ATK = ATK*1.2
    frostbite->modifier[2] = -0.85; // DEF of enemy *= 0.85 (it is negative to indicate that it affects the enemy)
    frostbite->duration_turn = 1; // lasts only that turn
}

void init_health_exchange(Skill *health_exchange){
    // Health exchange
    strcpy(health_exchange->name, "Health Exchange");
    strcpy(health_exchange->description, "If your health points are dangerously low and you think your enemy "
    "is healthier, use this to swap your health points with theirs. This can only be used once in a battle");
    health_exchange->type = 1; // direct attack
    health_exchange->modifier[0] = 1; // character HP will be swapped with enemy HP, but there is no multiplier
    health_exchange->modifier[1] = 1; // ATK is unchanged ATK = ATK*1
    health_exchange->modifier[2] =  1; // DEF is unchanged DEF = DEF*1
    health_exchange->duration_turn = 0; // swaps the HPs "forever"
}

void init_fireball(Skill *fireball){
    // Fireball
    strcpy(fireball->name, "Fireball");
    strcpy(fireball->description, "Launch a fireball towards your enemy, engulfing them in flames. "
    "This fiery assault deals damage equal to your attack points multiplied by 1.3. The intense heat "
    "from the fireball causes the enemy to burn, which also increases the damage they take in the next two rounds "
    "by 30 percent.");
    fireball->type = 0; // temporary modifier
    fireball->modifier[0] = 1; // HP is unchanged HP = HP*1
    fireball->modifier[1] = 1.3; // ATK = ATK*1.3
    fireball->modifier[2] = 1; // DEF is unchanged DEF = DEF*1
    fireball->duration_turn = 3; // modifies ATK points for 3 turns in total
}

void init_healing_aura(Skill *healing_aura){
    // Healing Auraa
    strcpy(healing_aura->name, "Healing Aura");
    strcpy(healing_aura->description, "Emit a healing aura, increasing your defence points by 30 percent "
    "against your enemy's next attack. Can be used without limit in a battle.");
    healing_aura->type = 0; // direct attack
    healing_aura->modifier[0] = 1; // HP is unchanged
    healing_aura->modifier[1] = 1; // ATK is unchanged ATK = ATK*1
    healing_aura->modifier[2] = 1; // DEF = DEF*1.3
    healing_aura->duration_turn = 2; // modifies DEF for the next turn, hence 2 (the current turn + next turn)
}

void init_thunderbolt(Skill *thunderbolt){
    // ThunderBolt
    strcpy(thunderbolt->name, "Thunder Bolt");
    strcpy(thunderbolt->description, "ThunderBolt: Summon a bolt of lightning to strike the enemy, "
    "increasing your attack points by 30 percent and decreasing the enemy's defence points by 10 percent. "
    "The attack leaves the enemy electrified so that its effects last for 2 turns in total");
    thunderbolt->type = 0; // temporal modifier
    thunderbolt->modifier[0] = 1; // HP is unchanged HP = HP*1
    thunderbolt->modifier[1] = 1.3; // ATK = ATK*1.3
    thunderbolt->modifier[2] = -0.9; // DEF of enemy *= 0.9 (it is negative to indicate that it affects the enemy)
    thunderbolt->duration_turn = 2; // modifies ATK points for that turn and the next
}

void init_time_warp(Skill *time_warp){
    // Time Warp
    strcpy(time_warp->name, "Time Warp");
    strcpy(time_warp->description, "Rewind time to restore half your initial health points."
    "Can only be used once per battle.");
    time_warp->type = 1; // direct attack
    time_warp->modifier[0] = 1; // HP will increment by 200 but there is no multiplier
    time_warp->modifier[1] = 1; // ATK is unchanged ATK = ATK*1
    time_warp->modifier[2] = 1; // DEF is unchanged DEF = DEF*1
    time_warp->duration_turn = 0; // modifies HP points "forever"
}

// Function that allows player to select 4 skills:
void init_character_skills(Character *new_character, Skill *shadow_blade, Skill *frostbite, Skill *health_exchange, 
                           Skill *fireball, Skill *healing_aura, Skill *thunderbolt, Skill *time_warp){
    // Let the player preview the skills (see a description of each before choosing)
    printf("\nIt is time to select the four skills that will help you battle your way through this quest. Choose "
    "wisely for your fate relies on them. You can view a description of each skill before selecting it using the menu below:\n"
    "1. Shadowblade strike\n2. Frostbite\n3. Health exchange\n4. Fireball\n5. Healing Aura\n6. ThunderBolt\n7. Time Warp\n");
    printf("\nEnter the number of the skill you wish to preview. When you are done previewing them enter -1: ");
    int skill_preview;
    scanf("%d", &skill_preview);
    while(skill_preview != -1){
        switch(skill_preview){
        case 1:
            printf("- %s:\n%s\n", shadow_blade->name, shadow_blade->description);
            break;
        case 2:
            printf("- %s:\n%s\n", frostbite->name, frostbite->description);
            break;
        case 3:
            printf("- %s:\n%s\n", health_exchange->name, health_exchange->description);
            break;
        case 4:
            printf("- %s:\n%s\n", fireball->name, fireball->description);
            break;
        case 5:
            printf("- %s:\n%s\n",healing_aura ->name, healing_aura->description);
            break;
        case 6:
            printf("- %s:\n%s\n",thunderbolt->name, thunderbolt->description);
            break;
        case 7:
            printf("- %s:\n%s\n", time_warp->name, time_warp->description);
            break;
        default: // In case the input is not a number in the menu
            printf("Invalid input\n");
        }
        printf("\nEnter the number of the skill you wish to preview. When you are done previewing them enter -1: ");
        scanf("%d", &skill_preview);
    }

    // Assigning the skills of the character:
    printf("\nNow that you have become familiar with the available skills. Enter the number of the skill that "
    "you wish to have:\n");
    for(int i=0; i<4; ++i){
        int selected_skill;
        printf("Skill %d: ", i+1);
        scanf("%d", &selected_skill);
        while(selected_skill < 1 || selected_skill > 7){
            //while the selected skill is not a number from 1 to 7, print error
            printf("Invalid input. Enter the number of the skill (from 1 to 7)");
            scanf("%d", &selected_skill);
        }
        switch(selected_skill){
            case 1:
                new_character->skills[i] = *shadow_blade;
                break;
            case 2:
                new_character->skills[i] = *frostbite;
                break;
            case 3:
                new_character->skills[i] = *health_exchange;
                break;
            case 4:
                new_character->skills[i] = *fireball;
                break;
            case 5:
                new_character->skills[i] = *healing_aura;
                break;
            case 6:
                new_character->skills[i] = *thunderbolt;
                break;
            case 7:
                new_character->skills[i] = *time_warp;
                break;
        }
    }
    printf("\nThe skills you have chosen are:\n");
    for(int i=0; i<4; i++){
        printf("- %s\n", new_character->skills[i].name);
    }
    printf("Good Luck!\n");
}