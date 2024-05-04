#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "struct_definitions.c"

int main(){
    // The third scenario is The Abandoned Castle:
    Scenario *castle = (Scenario*)malloc(sizeof(Scenario)); // Dynamic memory allocation for the scenario struct
    strcpy(castle->name, "Abandoned Castle");
    strcpy(castle->description, "The screen shifts to reveal an ancient castle "
    "enveloped in dense fog. Two paths diverge at the entrance, offering a crucial "
    "choice that will shape your journey ahead.");

    // The decision is wether to take the left or right path:
    Decision *choose_path = (Decision*)malloc(sizeof(Decision)); // Dynamic memory allocation for the decision struct
    castle->decision = choose_path;
    choose_path->num_options = 2;
    strcpy(choose_path->question_text, "Seeker of Gemstones, will you take" 
    " the left path and venture deep into the castle's crypt, or will you explore "
    "the right trail and wonder into the courtyard?");

    // The left path takes the player to a crypt:
    Option *crypt = (Option*)malloc(sizeof(Option)); // Dynamic memory allocation for the first option struct
    choose_path->options_list[0] = crypt;
    strcpy(crypt->response_text, "You descend into the depths of the crypt "
    "where secrets and unseen horrors await amongst the bones of past generations.");
    strcpy(crypt->narrative_text_before, "As you reach the crypt, a fearsome creature "
    "emerges from the darkness - a Ghoul. This undead being lurks in the shadows of the crypt, "
    "agile and relentless, it is capable of leaping from the darkness to attack unsuspecting prey.");
    strcpy(crypt->narrative_text_after, "With victory pulsing through your veins, you survey the aftermath "
    "of the battle. Among the debris of the crypt you see a pedestal, atop it lies the last fragment of the "
    "riddle. Anticipation grips you as you draw near, your hand reaches out to claim the ancient stone etched "
    "with the final words of the riddle.");
    crypt->num_enemies = 1;

    // The enemy of the crypt is a ghoul:
    Enemy *ghoul = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the enemy struct
    crypt->enemies[0] = *ghoul;
    strcpy(ghoul->name, "Ghoul");
    ghoul->points[0] = 200; // HP (when this reaches 0 the enemy is defeated)
    ghoul->points[1] = 20; // ATK (an attack reduces the player's HP by 20)
    ghoul->points[2] = 15; // DEF (blocks 15 ATK)

    // The right path takes the player to a courtyard:
    Option *courtyard = (Option*)malloc(sizeof(Option)); // Dynamic memory allocation for the second option struct
    choose_path->options_list[1] = courtyard;
    strcpy(courtyard->response_text, "You step into the wild courtyard, surrounded by towering "
    "hedges, crumbling statues, and at its heart, a weathered fountain. Mist rises from the "
    "overgrown algae, cloaking the scene in a mystical atmosphere.");
    strcpy(courtyard->narrative_text_before, "As you take in the eerie setting "
    "you suddenly sense a presence lurking amidst the overgrown greenery. Emerging "
    "from the shadows are two mighty adversaries.\nCarved from solid granite and brought to "
    "life by ancient sorcery, the Stone Guardian stands as the mighty protector of the "
    "courtyard. \nTaking a stance beside it is the Deadly Nightshade. This malevolent plant "
    "creature lurks among the wild foliage, with deadly vines and toxic flowers.");
    strcpy(courtyard->narrative_text_after, "Emerging victorious from the courtyard, a sense of "
    "accomplishment washes over you. Suddently, a shimmer of light from the fountain catches your "
    "eye. Drawing closer, you discover a hidden compartment within the weathered stone. With trembling "
    "hands, you retrieve the ancient artifact concealed within - a fragment of a runestone etched with "
    "the final words of the riddle.");
    courtyard->num_enemies = 2;

    // The first enemy of the courtyard is a stone guardian:
    Enemy *stone_guardian = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the first enemy struct
    courtyard->enemies[0] = *stone_guardian;
    strcpy(stone_guardian->name, "Stone Guardian");
    stone_guardian->points[0] = 150; // HP (when this reaches 0 the enemy is defeated)
    stone_guardian->points[1] = 15; // ATK (an attack reduces the player's HP by 15)
    stone_guardian->points[2] = 10; // DEF (blocks 10 ATK)

    // The second enemy of the courtyard is deadly nightshade:
    Enemy *deadly_nightshade = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the second enemy struct
    courtyard->enemies[1] = *deadly_nightshade;
    strcpy(deadly_nightshade->name, "Deadly Nightshade");
    deadly_nightshade->points[0] = 100; // HP (when this reaches 0 the enemy is defeated)
    deadly_nightshade->points[1] = 10; // ATK (an attack reduces the player's HP by 10)
    deadly_nightshade->points[2] = 5; // DEF (blocks 5 ATK)

    // The last scenario is The Battle for the Gemstones:
    Scenario *final_battle = (Scenario*)malloc(sizeof(Scenario)); // Dynamic memory allocation for the scenario struct
    strcpy(final_battle->name, "The Battle for the Gemstones");
    strcpy(final_battle->description, "As you emerge victorious from the towering castle, clutching the "
    "final shard of the riddle, the air crackles with anticipation. The time has come to solve the riddle "
    "that will guide you to the Sacred Gemstones. You can now piece together all the fragments you've gathered "
    "over the last three challenges. And as you do so, the puzzle unfolds before you, revealing the entirety "
    "of the riddle.");

    // The decision is the player's answer to the riddle:
    Decision *solve_riddle = (Decision*)malloc(sizeof(Decision)); // Dynamic memory allocation for the decision struct
    final_battle->decision = solve_riddle;
    solve_riddle->num_options = 1;
    strcpy(solve_riddle->question_text, "Brave adventurer, your path has led you to this critical moment. "
    "Before you lies the final mystery to unravel before claiming the gems. Listen closely:\nIt is the beginning "
    "of eternity,\nthe end of time and space,\nthe beginning of the end,\nand the end of every space.\nWhat is it?");
    
    // If the riddle is solved correctly, then the final battle can commence:
    Option *enter_final_battle = (Option*)malloc(sizeof(Option)); // Dynamic memory allocation for the option struct
    solve_riddle->options_list[0] = enter_final_battle;
    strcpy(enter_final_battle->response_text, "Congratulations! You've successfully solved the riddle! "
    "The answer is indeed the letter E.");
    strcpy(enter_final_battle->narrative_text_before, "In a flash, you find yourself transported to the location "
    "of the Sacred Gemstones. Their radiant glow captivates you, but a dangerous presence lurks nearby. Three adversaries "
    "stand guard, each embodying the essence of the gemstone they protect: time, space, and spirituality.\nThe Guardian of "
    "Time, spectral and adorned with ancient timepieces, disorients its opponents by manipulating time. The Guardian of Space, "
    "enveloped in swirling darkness, commands the environment to its advantage. The Guardian of Spirituality, radiant and ethereal, "
    "draws upon otherworldly powers to weaken its prey.\nPrepare yourself for the final battle, as the fate of the Sacred Gemstones "
    "rests in your hands.");
    strcpy(enter_final_battle->narrative_text_after, "With a final blow, you defeat the three adversaries, their forms disappearing "
    "into smoke. As the last guardian falls, a profound silence descends, broken only by the soft hum of the Sacred Gemstones in "
    "your grasp. The air shimmers with newfound energy as you feel the power coursing through you. Victorious, you hold the key "
    "to unlocking untold potential and shaping the destiny of the world. Then, before you, a final message appears in golden "
    "letters: 'Congratulations, adventurer! You have conquered the Trial of Ascension and emerged with the power of the Sacred Gemstones'.");
    enter_final_battle->num_enemies = 3;

    // The three enemies in this scenario are each associated with a gemstone (time, space and spirituality):
    // The first enemy is associated with time:
    Enemy *time_guardian = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the enemy struct
    enter_final_battle->enemies[0] = *time_guardian;
    strcpy(time_guardian->name, "Guardian of Time");
    time_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    time_guardian->points[1] = 30; // ATK (an attack reduces the player's HP by 20)
    time_guardian->points[2] = 20; // DEF (blocks 15 ATK)

    // The second enemy is associated with space:
    Enemy *space_guardian = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the first enemy struct
    enter_final_battle->enemies[1] = *space_guardian;
    strcpy(space_guardian->name, "Guardian of Space");
    space_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    space_guardian->points[1] = 20; // ATK (an attack reduces the player's HP by 15)
    space_guardian->points[2] = 15; // DEF (blocks 10 ATK)

    // The third enemy is associated with spirituality:
    Enemy *spirituality_guardian = (Enemy*)malloc(sizeof(Enemy)); // Dynamic memory allocation for the second enemy struct
    enter_final_battle->enemies[2] = *spirituality_guardian;
    strcpy(spirituality_guardian->name, "Guardian of Spirituality");
    spirituality_guardian->points[0] = 300; // HP (when this reaches 0 the enemy is defeated)
    spirituality_guardian->points[1] = 25; // ATK (an attack reduces the player's HP by 10)
    spirituality_guardian->points[2] = 20; // DEF (blocks 5 ATK)
}