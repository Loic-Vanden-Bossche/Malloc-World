//
// Created by Loïc Vanden Bossche on 28/11/2021.
//

#include "../headers/monster.h"

monster monsters[86] = {
        { 1, "Bane Bull" },
        { 2, "Black Fungus" },
        { 3, "Bloom Beast" },
        { 4, "Coffer Choker" },
        { 5, "Crimson Chopper-masher" },
        { 6, "Cursed Half" },
        { 7, "Draining Transposer-creature" },
        { 8, "Drowner-tracker" },
        { 9, "Glowillusion Beast" },
        { 10, "Grotesque Binder" },
        { 11, "Jelly Crystal" },
        { 12, "Leaf Roc" },
        { 13, "Lord Slay Shark" },
        { 14, "Moundmask" },
        { 15, "Netleech Reptile" },
        { 16, "Phantom Slicer" },
        { 17, "Rainbow Troll" },
        { 18, "Shredder-returned" },
        { 19, "Shrine Emperess" },
        { 20, "Sneak Dweller" },
        { 21, "Soul Shatterer" },
        { 22, "Sun Lizard" },
        { 23, "Tri Satyr" },
        { 24, "Vine Transposer" },
        { 25, "Wardream Drainer" },
        { 26, "Assasin Lurk" },
        { 27, "Black Mirage Sucker" },
        { 28, "Cosmic Dusk Goblin" },
        { 29, "Creeper-screamer" },
        { 30, "Creeping Shark" },
        { 31, "Crystalhorror" },
        { 32, "Dual Ember Brute" },
        { 33, "Final Gravel Phantom" },
        { 34, "Forestshade Eel" },
        { 35, "Half Beast-jelly" },
        { 36, "Hidden Lion" },
        { 37, "Hornet Emperor" },
        { 38, "Jelly Urchin" },
        { 39, "Liquidscum" },
        { 40, "Lunar Leaf" },
        { 41, "Night Piercer" },
        { 42, "Purple Sea Mold" },
        { 43, "Rope Flayer" },
        { 44, "Rope Plant" },
        { 45, "Rust Lump" },
        { 46, "Snowplant" },
        { 47, "Star Gorgon" },
        { 48, "Vulpine Fiend" },
        { 49, "Warlight Amoeba" },
        { 50, "Warlock Siren" },
        { 51, "Banshee Tearer" },
        { 52, "Burndream Lump" },
        { 53, "Emperess Fog Carver" },
        { 54, "Enveloper-slime" },
        { 55, "Fleshsapphire Hood" },
        { 56, "Greater Manipulator-piercer" },
        { 57, "Holy Stealth Creamator" },
        { 58, "King Dissector-grub" },
        { 59, "Legendary Elemental" },
        { 60, "Liquid Jaguar" },
        { 61, "Madnessomen Singer" },
        { 62, "Mawserpent Pixie" },
        { 63, "Meteorwave" },
        { 64, "Plant Bat" },
        { 65, "Poltergeist Deer" },
        { 66, "Searchingfen Swarm" },
        { 67, "Shade Roper" },
        { 68, "Spectral Twister Ape" },
        { 69, "Stonefang" },
        { 70, "Twistcanyon Lump" },
        { 71, "Twister Slug" },
        { 72, "Unthinkable Rainbow Slaughterer" },
        { 73, "Valeslash" },
        { 74, "Vaultfish Torturer" },
        { 75, "Warvortex Horse" },
        { 76, "Ancestral Brood Slasher" },
        { 77, "Ancient Dissolver-melter" },
        { 78, "Blasphemous Trunk Lord" },
        { 79, "Cold Babbler-shocker" },
        { 80, "Comet Ray" },
        { 81, "Cometchild" },
        { 82, "Cyclops Mongrel" },
        { 83, "Demon Wolverine" },
        { 84, "Demonic Secret Lich" },
        { 85, "Freezing Cleaver-spectator" },
        { 86, "Great Bull" },
};

void generateMonsters() {

    for (int i = 0; i < 86; ++i) {
        monsters[i].lvl = (i/8)+1;

        monsters[i].maxHp = 100 * pow(1.2, monsters[i].lvl - 1);
        monsters[i].damages = pow(1.3, monsters[i].lvl - 1);
    }
}

void displayMonsters() {

    for (int i = 0; i < 86; ++i) {
        printf("%d | %d | %d | %d | %s\n",monsters[i].id, monsters[i].lvl, monsters[i].maxHp, monsters[i].damages, monsters[i].name);
    }
}

monster* getMonsterById(int id) {
    for (int i = 0; i < 86; ++i)
        if (monsters[i].id == id) return &monsters[i];

    return NULL;
}

const char* getRandomBossName() {

    const char* randomBossName[20] = {
            "Etdar , God of  Duty",
            "Moysus , God of  Truth",
            "Hapdar , God of  Fame\n"
            "Addia, Godess of  Abundance\n"
            "Kovlene, Godess of  the Ocean\n"
            "Iztuna, Godess of  the Moon",
            "Urrena, Godess of  Hope\n"
            "Itune, Godess of  Chivalry\n"
            "Kygyn, Godess of  Order",
            "Tozris, Godess of  Endings",
            "Uqmus , God of  Forgiveness",
            "Nanohr , God of  the Military\n"
            "Ikros , God of  Day",
            "Ylruer , God of  Virtues",
            "Icnos , God of  the Mountains",
            "Nelmis, Godess of  the Hearth",
            "Sigona, Godess of  Earth\n"
            "Acdea, Godess of  Blacksmiths\n"
            "Atix, Godess of  Infamy",
            "Uulla, Godess of  the Insane\n"
            "Kipella, Godess of  the Stars",
            "Ruysus , God of  Weddings",
            "Dapaldir , God of  the Afterlife",
            "Judros , God of  Mercy",
            "Yborh , God of  Poetry",
            "Dyhnos , God of  Science",
            "Zybdohr , God of  Conquest",
            "Fumteus , God of  Beginnings",
            "Litnir , God of  Fortune"
    };

    return randomBossName[getRandomNumber(0, 20)];
}

int fightMenu() {

    printf("1 - Frapper\n");
    printf("2 - Utiliser une potion\n");
    printf("3 - Equiper une autre arme\n");

    char ch;

    while(1) {

        fflush(stdin);
        ch = getchar();

        switch(ch) {
            case '1' ... '3':
                return ch - '0';
        }
    }
}

const itemData* getBestWeapon(item inventory[10]) {
    const itemData* weaponRef = NULL;

    for (int i = 0; i < 10; ++i) {
        const itemData* data = getItemData(inventory[i].id);

        if(data != NULL) {
            if(data->type == WEAPON) {
                if(weaponRef != NULL) {
                    if(weaponRef->damages < data->damages) weaponRef = data;
                } else {
                    weaponRef = data;
                }
            }
        }
    }

    return weaponRef;
}

void applyDamages(int* hp, int damages) {

    *hp = ((*hp - damages) < 0) ? 0 : *hp - damages;
}

void fightMonster(int monsterId, player* player) {

    const monster* monsterData = getMonsterById(monsterId);

    if(monsterData == NULL) return;

    int monsterHp = monsterData->maxHp;
    
    const itemData* equippedWeapon = getBestWeapon(player->inventory);

    if(equippedWeapon == NULL) {
        debug("Vous n'avez aucune arme !!\n Vous ne pouvez pas combattre !!\n");
        return;
    }

    debug("Vous combattez le monstre : %s de niveau %d\n", monsterData->name, monsterData->lvl);
    debug("Votre arme est : %s\n", equippedWeapon->name);

    while(monsterHp > 0 && player->hp > 0) {

        switch(fightMenu()){
            case 1:
                debug("Vous infligez %d de dégâts au monstre !!\n", equippedWeapon->damages);
                applyDamages(&monsterHp, equippedWeapon->damages);
                break;
            case 2:
                break;
            case 3:
                break;
        }

        debug("Le monstre attaque !!\n");

        debug("Le monstre vous a infligé %d de dégâts !!\n", monsterData->damages);
        applyDamages(&player->hp, monsterData->damages);

        debug("PHP : %d | MHP : %d\n", player->hp, monsterHp);
    }
}