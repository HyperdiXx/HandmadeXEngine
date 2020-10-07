#ifndef TREE_CPP
#define TREE_CPP

struct Quadtree
{
    enum
    {
        TL,
        TR,
        BL,
        BR
    };

    Rect quad;

    uint32 current_level, max_level;

    Quadtree *top_left = NULL;
    Quadtree *top_right = NULL;

    Quadtree *bottom_left = NULL;
    Quadtree *bottom_right = NULL;

    DynArray<Rect*> objects;

    Quadtree() {}
    Quadtree(real32 x, real32 y, real32 width, real32 height, uint32 level, uint32 max)
    {
        quad = createRect(x, y, width, height);
        current_level = level;
        max_level = max;

        objects = createDynArray<Rect*>();

        if (level < max)
        {
            real32 half_width = width * 0.5f;
            real32 half_height = height * 0.5f;

            top_left  = new Quadtree(x, y + half_height, half_width, half_height, level + 1, max);
            top_right = new Quadtree(x + half_width, y + half_height, half_width, half_height, level + 1, max);

            bottom_left = new Quadtree(x, y, half_width, half_height, level + 1, max);
            bottom_right = new Quadtree(x + half_width, y, half_width, half_height, level + 1, max);
        }
    }

    ~Quadtree()
    {
        if (!top_left)
        {
            return;
        }

        delete top_left;
        delete top_right;

        delete bottom_left;
        delete bottom_right;
    }
};

inline bool inside(const Quadtree *tree, const Rect *rect)
{
    return !(rect->x < tree->quad.x ||
            rect->y < tree->quad.y ||
            rect->x > tree->quad.x + tree->quad.width ||
            rect->y > tree->quad.y + tree->quad.height ||
            rect->x + rect->width < tree->quad.x ||
            rect->y + rect->height < tree->quad.y ||
            rect->x + rect->width > tree->quad.x + tree->quad.width ||
            rect->y + rect->height > tree->quad.y + tree->quad.height);
}

inline void addObject(Quadtree *tree, Rect *rect)
{
    if (tree->current_level == tree->max_level)
    {
        tree->objects.push_back(rect);
        return;
    }

    if (inside(tree->top_left, rect))
    {
        addObject(tree->top_left, rect);
        return;
    }
    else if (inside(tree->top_right, rect))
    {
        addObject(tree->top_right, rect);

        return;
    }
    else if (inside(tree->bottom_left, rect))
    {
        addObject(tree->bottom_left, rect);

        return;
    }
    else if (inside(tree->bottom_right, rect))
    {
        addObject(tree->bottom_right, rect);

        return;
    }

    if (inside(tree, rect))
    {
        tree->objects.push_back(rect);
    }
}

#endif // !TREE_H
