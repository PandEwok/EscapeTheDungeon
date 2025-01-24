#pragma once

#include "Global.hpp";
#include "Entity.hpp"

class Interactable {
public:
	virtual void interact(Player& player) = 0;
};

class Coin : public Entity, public Interactable {
public:
	Coin();
	void interact(Player& player) override;
	void draw() override;
};

class PotionHeal : public Entity, public Interactable {
public:
	PotionHeal();
	void interact(Player& player) override;
	void draw() override;
};

class Key : public Entity, public Interactable {
public:
	Key();
	void interact(Player& player) override;
	void draw() override;
};