#include "Blend.h"
#include <GL/glew.h>

void Blend::Enable()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void Blend::Disable()
{
	glDisable(GL_BLEND);
}
