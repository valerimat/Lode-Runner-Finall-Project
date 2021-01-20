#include "Lives.h"
#include "Macros.h"

Lives::Lives()
{
	set_lives();
}
void Lives::set_lives()
{
	m_lives = BASE_LIVES;
}
int Lives::get_lives()
{
	return m_lives;
}
void Lives::dec_lives()
{
	--m_lives;
}
void Lives::add_lives()
{
	++m_lives;
}