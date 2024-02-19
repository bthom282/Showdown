#ifndef RENDERER_H
#define RENDERER_H

void game_start();

void render(const Model *model, UINT32 *base);

void render_bullets(const *Bullet, UINT8 *base);

void render_cowboy(const *Cowboy, UINT32 *base);

void render_snakes(const *Snake, UINT32 *base);

void render_score{const *Score, UINT8 *base);

void render_lives{const *Lives, UINT16 *base);

#endif
