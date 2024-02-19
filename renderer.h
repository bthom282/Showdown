#ifndef RENDERER_H
#define RENDERER_H

void game_start();

void render(struct Model *model, UINT32 *base);

void render_cowboy(UINT32 *base, struct Cowboy cowboy);

void render_bullets(UINT8 *base, struct Bullet *active_bullets, const UINT8 *bitmap8, int bullets_fill);

void render_snakes(UINT32 *base, struct Snake *active_snakes, int snakes_fill);

void render_side_panel(UINT16 *base);

void render_level1(UINT16 *base, const UINT32 *bitmap);

void render_score(const *Score, UINT8 *base);

void render_lives(const *Lives, UINT16 *base);

#endif
