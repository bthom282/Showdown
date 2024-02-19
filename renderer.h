#ifndef RENDERER_H
#define RENDERER_H

void game_start();

void render(const Model *model, UINT32 *base);

void render_bullets(UINT8 *base, struct Bullet *active_bullets, const UINT8 *bitmap8, int bullets_fill);

void render_cowboy(UINT32 *base, const *Cowboy);

void render_snakes(UINT32 *base, );

void render_score{const *Score, UINT8 *base);

void render_lives{const *Lives, UINT16 *base);

#endif
