#include "Lives.h"
#include "Macros.h"

Lives::Lives()
{
	SetLives();
}
void Lives::SetLives()
{
	m_lives = BASE_LIVES;
}
int Lives::GetLives()
{
	return m_lives;
}
void Lives::DecLives()
{
	--m_lives;
}
void Lives::AddLives()
{
	++m_lives;
}