#include "Sw.h"
using namespace std;
namespace NevClient
{
	namespace SwLogic
	{
		VOID Pursuit_Long_flash(uintptr_t Player, uintptr_t Enemy)
		{
			int i = 0;
			if (!AttackMode::Fixed.load() || !AttackMode::Attackable.load() || GameTool::GetPropertyData(Memory::RPM<uintptr_t>(Player + ActorModel_RuntimePropertyData)).CurEnergy < GameTool::GetPropertyData(Memory::RPM<uintptr_t>(Player + ActorModel_RuntimePropertyData)).ConsumEnergy)
			{
				bool CC = false;
				if (Tool::_GetAsyncKeyState('C') >= 0) {
					Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
				}
				uintptr_t MaxAttackTime = GetTickCount64() + 400 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(LocalState, regex("(female|male)_\\w+_crouch(_idle|_run)_\\d+$")))
					{
						if (Tool::_GetAsyncKeyState('C') & 0x8000) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(20));
						}
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						CC = true;
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (CC)
				{
					if (GameTool::GetPropertyData(Memory::RPM<uintptr_t>(Player + ActorModel_RuntimePropertyData)).CurEnergy > GameTool::GetPropertyData(Memory::RPM<uintptr_t>(Player + ActorModel_RuntimePropertyData)).ConsumEnergy)
					{
						if (Tool::_GetAsyncKeyState('S') >= 0) {
							Tool::_keybd_event('S', MapVirtualKey('S', 0), 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
						}
						const uintptr_t MaxTime3 = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
						while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, regex("(female|male)_\\w+_crouch_dodge_\\w+_\\d+.*")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState('S') & 0x8000) {
							Tool::_keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
					}
					else
					{
						if (Tool::_GetAsyncKeyState('C') >= 0) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
						}
						uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+(_idle|_run)_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState('C') & 0x8000) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}

				}
				return;
			}
			string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
			if (regex_match(EnemyState, AllAttack::Enemy_Parry))
			{
				if (Tool::_GetAsyncKeyState('S') >= 0) {
					Tool::_keybd_event('S', MapVirtualKey('S', 0), 0, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
					Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
				}
				const uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
					string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(State, AllAttack::Enemy_dodge)) {
						if (Tool::_GetAsyncKeyState('S') & 0x8000) {
							Tool::_keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				return;
			}
			if (Tool::_GetAsyncKeyState('W') >= 0) {
				Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
				this_thread::sleep_for(chrono::milliseconds(15));
			}
			if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
				Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
			}
			const uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
			while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
				string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(State, AllAttack::Enemy_dodge)) {
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					i = 1;
					break;
				}
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (i != 1)
			{
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
					Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				if (Tool::_GetAsyncKeyState('W') & 0x8000) {
					Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
					Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				return;
			}
			if (i == 1)
			{
				const uintptr_t MaxTime3 = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
				while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
					string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(State, regex("(female|male)_\\w+_sprint_start_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (!regex_match(LocalState, regex("(female|male)_\\w+_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+(_pre|_charge)$")))
						{

							if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0 && Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
							}
							i = 2;
							break;
						}
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
			}
			if (i == 2)
			{
				const uintptr_t MaxTime3 = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
				while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
					string LocalHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(LocalHit, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+(_pre|_charge)$")))
					{
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
			}
			if (Tool::_GetAsyncKeyState('W') & 0x8000) {
				Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
				Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			return;
		}


		VOID Crouch_heavy_Attack(uintptr_t Player, uintptr_t Enemy)
		{
			int i = 0;
			const uintptr_t MaxAttackTime = GetTickCount64() + 600 + static_cast<int>(GameGlobal::GamePing * 2000);
			while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
			{
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_\\w+_crouch_attack_heavy_\\d+$")))
				{
					i = 1;
					break;
				}
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (i == 1)
			{
				bool Attack = false;
				const uintptr_t MaxAttackTime = GetTickCount64() + 300 + static_cast<int>(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
					if (regex_match(EnemyState, AllAttack::Enemy_Parry))
					{
						return;
					}
					if (GameTool::IsHiting(Enemy))
					{
						//Tool::DbgPrint("%ws - %ws - %x - %x - %f", Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str, Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str, GameTool::Get_EnableInputCache(Player), GameTool::Get_CurrentBreakMask(Player), GameTool::GetCurTimeForLogicState(Player));
						//this_thread::sleep_for(chrono::milliseconds(100));
						//Tool::DbgPrint("%ws - %ws - %x - %x - %f", Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str, Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str, GameTool::Get_EnableInputCache(Player), GameTool::Get_CurrentBreakMask(Player), GameTool::GetCurTimeForLogicState(Player));
						//if (Tool::_GetAsyncKeyState('W') >= 0) {
						//	Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
						//}
						if (KatanaGlobal::AttackMode == 1)
						{
							if (Tool::_GetAsyncKeyState('Q') >= 0) {
								this_thread::sleep_for(chrono::milliseconds(30));
								Tool::_keybd_event('Q', MapVirtualKey('Q', 0), 0, 0);
							}
							if (Tool::_GetAsyncKeyState('Q') & 0x8000) {
								Tool::_keybd_event('Q', MapVirtualKey('Q', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
						Attack = true;
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (Attack)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 600 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (KatanaGlobal::AttackMode == 0)
						{
							if (GameTool::Get_CurrentBreakMask(Player) == 0x14000)//0x10182
							{
								if (Tool::_GetAsyncKeyState('W') >= 0) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								}
								i = 2;
								break;
							}
						}
						else if (KatanaGlobal::AttackMode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Player) > 0.12f && GameTool::GetCurTimeForLogicState(Player) <= 0.2f)
							{
								i = 2;
								break;
							}
						}
						else if (KatanaGlobal::AttackMode == 2)
						{
							if (GameTool::GetCurTimeForLogicState(Player) >= 0.276f)
							{
								if (Tool::_GetAsyncKeyState('W') >= 0) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
								}
								i = 2;
								break;
							}
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else
				{
					return;
				}
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
			}
			if (i == 2)
			{
				if (KatanaGlobal::AttackMode == 0)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 300 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_jump_attack_\\d+_pre$")))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_sw_jump_attack_\\d+$")))
						{
							i = 3;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 1)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 250 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::IsChainState(Player) == 2)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(20));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(20));
							}
							i = 3;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 2)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_down_to_land_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_square_\\w+_\\d+$")) || GameTool::Get_EnableInputCache(Player) == 0x800e43 || GameTool::Get_EnableInputCache(Player) == 0x2800e43)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
							}
							i = 3;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
			}
			if (i == 3)
			{
				if (KatanaGlobal::AttackMode == 0)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_down_to_land_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_square_\\w+_\\d+$")) || GameTool::Get_EnableInputCache(Player) == 0x800e43 || GameTool::Get_EnableInputCache(Player) == 0x2800e43)
						{
							if (Tool::_GetAsyncKeyState(VK_SPACE) >= 0) {
								Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), 0, 0);
							}
							i = 4;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 1)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 1200 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_aim_hook_grapple_jump_\\d+$")))
						{
							if (Tool::_GetAsyncKeyState('D') >= 0) {
								Tool::_keybd_event('D', MapVirtualKey('D', 0), 0, 0);
							}
							i = 4;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 2)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 600 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_heavy_01_pre$")))
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_heavy_01$")))
						{
							i = 4;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
			}
			if (i == 4)
			{
				if (KatanaGlobal::AttackMode == 0)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 500 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_\\w+_up_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_jump_inplace_up_\\d+$")))
						{
							if (Tool::_GetAsyncKeyState(VK_SPACE) & 0x8000) {
								Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 5;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 1)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_down_to_land_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_square_\\w+_\\d+$")) || GameTool::Get_EnableInputCache(Player) == 0x800e43 || GameTool::Get_EnableInputCache(Player) == 0x2800e43)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState('D') & 0x8000) {
								Tool::_keybd_event('D', MapVirtualKey('D', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 5;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 2)
				{
					uintptr_t MaxAttackTime = GetTickCount64() + 800 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_CurrentBreakMask(Player) == 0x1c102 || GameTool::Get_CurrentBreakMask(Player) == 0xc102)
						{
							i = 5;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
			}
			if (i == 5)
			{
				if (KatanaGlobal::AttackMode == 0)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}
					const uintptr_t MaxAttackTime = GetTickCount64() + 300 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_jump_attack_\\d+_pre$")))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_sw_jump_attack_\\d+$")))
						{
							i = 6;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}

				}
				else if (KatanaGlobal::AttackMode == 1)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::PlayerIsLastChargePhase(Player) == 1)
						{
							if (GameTool::IsHiting(Enemy))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								break;
							}
							else
							{
								return;
							}

						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else if (KatanaGlobal::AttackMode == 2)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					}
					const uintptr_t MaxAttackTime = GetTickCount64() + 600 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_light_02_pre$")))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_light_02$")))
						{
							if (Tool::_GetAsyncKeyState('W') & 0x8000) {
								Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							}
							i = 6;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				if (GameTool::IsHiting(Player))
				{
					GameTool::Keyup();
					return;
				}
			}
			if (i == 6)
			{
				if (KatanaGlobal::AttackMode == 0)
				{
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_down_to_land_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_\\d+$")) || regex_match(LocalState, regex("(female|male)_\\w+_run_start_square_\\w+_\\d+$")) || GameTool::Get_EnableInputCache(Player) == 0x800e43 || GameTool::Get_EnableInputCache(Player) == 0x2800e43)
						{
							if (Tool::_GetAsyncKeyState('W') & 0x8000) {
								Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							}
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState('W') & 0x8000) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
					}
				}
				else if (KatanaGlobal::AttackMode == 2)
				{
					bool Cmask = false;
					const uintptr_t MaxAttackTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_CurrentBreakMask(Player) == 0x1c102 || GameTool::Get_CurrentBreakMask(Player) == 0xc102)//0x10182
						{
							Cmask = true;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Cmask)
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						}
						const uintptr_t MaxAttackTime = GetTickCount64() + 600 + static_cast<int>(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::PlayerIsLastChargePhase(Player) == 1)
							{
								if (GameTool::IsHiting(Enemy))
								{
									if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
										Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									}
									break;
								}
								else
								{
									return;
								}

							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}

					}
				}
			}
			return;
		}

		VOID Two_Attack(uintptr_t Player, uintptr_t Enemy)
		{
			bool Right_Attack_State = false;
			int State = 0;
			uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
			while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
			{
				if (GameTool::Get_EnableInputCache(Player) == 0x1c102 && !Right_Attack_State)
				{
					Right_Attack_State = true;
				}
				if (Right_Attack_State)
				{
					Pursuit_Long_flash(Player, Enemy);
					break;
				}
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			return;
		}

		VOID One_Attack(uintptr_t Player, uintptr_t Enemy)
		{
			bool Right_Attack_State = false;
			int State = 0;
			uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
			while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
			{
				if (GameTool::Get_EnableInputCache(Player) == 0x1c102 && !Right_Attack_State)
				{

					Right_Attack_State = true;
				}
				if (Right_Attack_State)
				{
					string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
					if (regex_match(EnemyState, regex("(female|male)_\\w+_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+_charge$")))
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
					if (GameTool::IsHiting(Enemy))
					{
						State = 1;
						break;
					}
				}
				this_thread::sleep_for(chrono::milliseconds(1));
			}
			if (State == 0)
			{
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());

				if (regex_match(LocalState, AllWeapon::Enemy_Bounce)) {
					return;
				}
				else if (regex_match(EnemyState, AllAttack::Enemy_Parry)) {
					return;
				}
				else if (regex_match(EnemyState, regex("(female|male)_\\w+_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+(_charge)*$")) || regex_match(EnemyState, AllAttack::Enemy_dodge)
					|| regex_match(EnemyState, AllAttack::Enemy_Longdodge)
					|| regex_match(EnemyState, AllAttack::Enemy_LongdodgeA)
					)
				{
					Pursuit_Long_flash(Player, Enemy);
					return;

				}
				if (AttackMode::foundChargeEnemy)
				{
					bool S_Attack = false;
					uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_CurrentBreakMask(Player) == 0x1c102 || GameTool::Get_CurrentBreakMask(Player) == 0xc102)
						{
							S_Attack = true;
							break;

						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (S_Attack)
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						}
						uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_\\d+_charge$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						return;
					}
					else
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
				}
				else
				{
					bool S_Attack = false;
					uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_CurrentBreakMask(Player) == 0x1c102 || GameTool::Get_CurrentBreakMask(Player) == 0xc102)
						{
							S_Attack = true;
							break;

						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (S_Attack)
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						}
						uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_02_pre$")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
							}
							if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_02$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					else
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
				}

				return;
			}
			if (State == 1)
			{
				if (AttackMode::foundChargeEnemy)
				{
					int S_Attack = false;
					uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_CurrentBreakMask(Player) == 0x1c102 || GameTool::Get_CurrentBreakMask(Player) == 0xc102)
						{
							S_Attack = true;
							break;

						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (S_Attack)
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						}
						uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_\\d+_charge$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						return;
					}
					else
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
				}
				else
				{
					if (GameTool::Get_EntityPercentage2D(Player, Enemy) <= 2.5f)
					{
						if (Tool::_GetAsyncKeyState('S') >= 0) {
							Tool::_keybd_event('S', MapVirtualKey('S', 0), 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
					}
					else
					{
						if (Tool::_GetAsyncKeyState('W') >= 0) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
					}
					uintptr_t MaxAttackTime = GetTickCount64() + 500 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, AllAttack::Enemy_dodge))
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_\\w+_sprint_start_\\d+.*")) || regex_match(LocalState, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
							}
							State = 2;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

			}
			if (State == 2)
			{
				ULONG64 MaxAttackTime1 = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime1 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_\\d+_pre$")))
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						}
					}
					if (std::regex_match(LocalState, std::regex("(female|male)_sw(_sprint|_run)*_attack_heavy_\\d+$")))
					{
						if (Tool::_GetAsyncKeyState('S') & 0x8000) {
							Tool::_keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						State = 3;
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
			}
			if (State == 3)
			{
				uintptr_t MaxAttackTime = GetTickCount64() + 200 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					if (GameTool::Get_EnableInputCache(Player) == 0x1c102)
					{
						string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
						if (regex_match(EnemyState, AllAttack::Enemy_Parry))
						{
							Pursuit_Long_flash(Player, Enemy);
							return;
						}
						if (!GameTool::IsHiting(Enemy))
						{
							Pursuit_Long_flash(Player, Enemy);
							return;
						}
						State = 4;
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
			}
			if (State == 4)
			{
				uintptr_t MaxAttackTime = GetTickCount64() + 300 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					if (GameTool::IsHiting(Enemy))
					{
						if (Tool::_GetAsyncKeyState('C') >= 0) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState('C') & 0x8000) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (std::regex_match(LocalState, std::regex("(female|male)_\\w+_squat(_run)*_\\d+$")))
						{
							string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
							if (!regex_match(EnemyState, regex("(female|male)_injured.*")) && !regex_match(EnemyState, regex("(female|male)_blade_parry_\\d+")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								}
								State = 5;
								break;
							}

						}
					}
					else
					{
						return;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
			}
			if (State == 5)
			{
				uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_heavy_\\d+_pre$")))
					{
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						}
					}
					if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_heavy_\\d+$")))
					{
						break;
					}
				}
			}
		}

		VOID Start_Attack(uintptr_t Player, uintptr_t Enemy)
		{
			ULONG64 CanHoldAttack = NULL;
			ULONG64 KsAttack = NULL;
			bool NearbyEnemies = !AttackMode::foundChargeEnemyList.empty();;
			unordered_map<ULONG64, ULONG>::const_iterator it = AttackMode::foundChargeEnemyList.begin();
			for (; it != AttackMode::foundChargeEnemyList.end(); ++it) {
				ULONG64 Object = it->first;
				if (Object != Enemy && GameTool::Get_EntityPercentage2D(Player, Object) <= 5.f) {
					string EnemyHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Object)).str).get());
					ULONG64 Mesh = Memory::RPM<ULONG64>(Object + ActorModel_actorVisual);
					Vector3 head = GameTool::GetBonePos(Mesh, 67);
					if (GameTool::WorldToScreen(&head)) {
						KsAttack = Object;
						if (regex_match(EnemyHit, AllAttack::Local_Shock) || regex_match(EnemyHit, AllAttack::Enemy_emptystep) || GameTool::GetHeroContinueLogic(Object) == 9) { //ÃÌº”Œ‰ÃÔbuff
							CanHoldAttack = Object;
						}
					}
				}
			}
			string EnemyHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
			unordered_map<string, ULONG64> actionTickMap = {};
			if (DataMap::PlayerActionTickMap.find(Enemy) != DataMap::PlayerActionTickMap.end()) {
				actionTickMap = DataMap::PlayerActionTickMap.at(Enemy);
			}
			if (KsAttack)
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && !CanHoldAttack)
				{
					if (GameTool::Get_EntityPercentage2D(Player, KsAttack) <= 5.f)
					{
						string EnemyHitTow(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(KsAttack)).str).get());
						if (regex_match(EnemyHit, AllAttack::Local_Shock) || regex_match(EnemyHitTow, AllAttack::Local_Shock))
						{
							if (Tool::_GetAsyncKeyState('S') >= 0) {
								Tool::_keybd_event('S', MapVirtualKey('S', 0), 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
								Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
							}
							const ULONG64 MaxTime = GetTickCount64() + 800 + static_cast<int>(GameGlobal::GamePing * 2000);
							while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(State, AllAttack::Enemy_dodge))
								{
									if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
										Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
										this_thread::sleep_for(chrono::milliseconds(15));
									}
									if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
										Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
										this_thread::sleep_for(chrono::milliseconds(15));
									}
									if (Tool::_GetAsyncKeyState('S') & 0x8000) {
										Tool::_keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);
										this_thread::sleep_for(chrono::milliseconds(15));
									}
									if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
										Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
										this_thread::sleep_for(chrono::milliseconds(15));
									}
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState('S') & 0x8000) {
								Tool::_keybd_event('S', MapVirtualKey('S', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
								Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							return;
						}

						if (GameTool::Get_Percentage(KsAttack) > 0.2f && !regex_match(EnemyHit, AllAttack::Enemy_emptystep) && !regex_match(EnemyHit, AllAttack::Local_Shock))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									return;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
						if (regex_match(EnemyHitTow, AllAttack::Enemy_Stand) || regex_match(EnemyHitTow, AllAttack::Enemy_Fly) || regex_match(EnemyHitTow, AllAttack::Enemy_Shock) ||
							regex_match(EnemyHitTow, AllAttack::Enemy_injured) || regex_match(EnemyHitTow, regex("(female|male)_frozen_\\d+$")) ||
							regex_match(EnemyHitTow, regex("(female|male)_all_wind_pressure_idle_\\d+$")) || regex_match(EnemyHitTow, regex("(female|male)_stun_\\d+$")) ||
							regex_match(EnemyHitTow, regex("(female|male)_yueshan_hurt_fly_\\d+$")) || regex_match(EnemyHitTow, regex("(female|male)_hero_takeda_skill_hurt_\\d+$")) ||
							regex_match(EnemyHitTow, regex("(female|male)_all_unarmed_be_tied_\\d+$"))
							&& !regex_match(EnemyHit, AllAttack::Enemy_emptystep) && !regex_match(EnemyHit, AllAttack::Local_Shock))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									return;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
						if (regex_match(EnemyHitTow, AllWeapon::Enemy_SlideAttack) || regex_match(EnemyHitTow, AllWeapon::Enemy_JumpAttack)
							|| regex_match(EnemyHitTow, AllWeapon::Enemy_CrouchLightAttack) || regex_match(EnemyHitTow, AllWeapon::Enemy_CrouchLightAttack2)
							|| regex_match(EnemyHitTow, AllWeapon::Enemy_Attack) || regex_match(EnemyHitTow, AllWeapon::Enemy_GlideAttack)
							|| regex_match(EnemyHitTow, AllWeapon::Enemy_CrouchHeavyAttack) || regex_match(EnemyHitTow, AllWeapon::Enemy_CrouchHeavyAttack2)
							&& !regex_match(EnemyHit, AllAttack::Enemy_emptystep) && !regex_match(EnemyHit, AllAttack::Local_Shock))
						{
							if (GameTool::GetCurTimeForLogicState(KsAttack) <= 0.45f && GameTool::GetCurTimeForLogicState(KsAttack) >= 0.1f)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								const ULONG64 MaxAttackTime = GetTickCount64() + 500;
								while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
								{
									string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
									if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
									{
										return;
									}
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
						}
					}
				}
			}


			if (!regex_match(EnemyHit, AllWeapon::Enemy_AttackPre)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_charge) && !regex_match(EnemyHit, AllWeapon::Enemy_charge2)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_charge3) && !regex_match(EnemyHit, AllAttack::Enemy_emptystep)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_SlideAttack) && !regex_match(EnemyHit, AllWeapon::Enemy_JumpAttack)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_CrouchLightAttack) && !regex_match(EnemyHit, AllWeapon::Enemy_CrouchLightAttack2)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_Attack) && !regex_match(EnemyHit, AllWeapon::Enemy_HoldAttack)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_HoldAttack2) && !regex_match(EnemyHit, AllWeapon::Enemy_HoldAttack3)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_CrouchHeavyAttack) && !regex_match(EnemyHit, AllWeapon::Enemy_CrouchHeavyAttack2)
				&& !regex_match(EnemyHit, AllAttack::Local_Shock) && !regex_match(EnemyHit, AllAttack::Enemy_dodge)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_GlideAttack) && !regex_match(EnemyHit, AllWeapon::Enemy_SpiritsMan)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_SpiritsMan2) && !regex_match(EnemyHit, AllWeapon::Enemy_SpiritsManDodgeDouble)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_guqinghan) && !regex_match(EnemyHit, AllAttack::Enemy_nunchucks_Parry)
				&& !regex_match(EnemyHit, AllAttack::Enemy_Parry) && !regex_match(EnemyHit, AllAttack::Enemy_getup)
				&& !regex_match(EnemyHit, AllWeapon::Enemy_Bounce))
			{
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (!regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_03(_pre|_charge)$")))
				{
					if (GameTool::GetEnergy(Player) < 0.5f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						string EnemyHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
						if (!regex_match(EnemyHit, regex("(female|male)_\\w+_sprint_inertia_\\d+$"))
							&& !regex_match(EnemyHit, regex("(female|male)_injured.*$"))
							&& !regex_match(EnemyHit, regex("(female|male)_hurt_(stand|fly).*$"))
							&& !regex_match(EnemyHit, AllAttack::Enemy_Shock)
							&& !regex_match(EnemyHit, AllWeapon::Enemy_guqinghan_Attack)
							&& !regex_match(EnemyHit, AllWeapon::Enemy_AttackPre)
							&& !regex_match(EnemyHit, AllWeapon::Enemy_charge)
							&& !regex_match(EnemyHit, AllWeapon::Enemy_charge2)
							&& !regex_match(EnemyHit, AllWeapon::Enemy_charge3))
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$")))
								{
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							return;
						}
					}
				}

				if (GameTool::GetEnergy(Player) >= 0.5f && !CanHoldAttack && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						string EnemyHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
						if (GameTool::Get_Percentage(Enemy) > 0.2f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									return;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
						if (regex_match(EnemyHit, AllAttack::Enemy_Stand) || regex_match(EnemyHit, AllAttack::Enemy_Fly) ||
							regex_match(EnemyHit, AllAttack::Enemy_injured) || regex_match(EnemyHit, regex("(female|male)_frozen_\\d+$")) ||
							regex_match(EnemyHit, regex("(female|male)_all_wind_pressure_idle_\\d+$")) || regex_match(EnemyHit, regex("(female|male)_stun_\\d+$")) ||
							regex_match(EnemyHit, regex("(female|male)_yueshan_hurt_fly_\\d+$")) || regex_match(EnemyHit, regex("(female|male)_hero_takeda_skill_hurt_\\d+$")) ||
							regex_match(EnemyHit, regex("(female|male)_all_unarmed_be_tied_\\d+$")))
						{
							if (GameTool::Get_Percentage(Enemy) > 0.f)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								const ULONG64 MaxAttackTime = GetTickCount64() + 500;
								while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
								{
									string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
									if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
									{
										return;
									}
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
						}
					}
				}

			}
			if (regex_match(EnemyHit, AllAttack::Enemy_dodge))
			{
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_03(_charge)$"))) {
					Pursuit_Long_flash(Player, Enemy);
					return;
				}
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::GetCurTimeForLogicState(Enemy) > 0 && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f)
				{
					if (!CanHoldAttack && GameTool::GetHeroContinueLogic(Enemy) != 9)
					{
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						const uintptr_t MaxAttackTime = GetTickCount64() + 500;
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						return;
					}
					else
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
				}
				else
				{
					if (GameTool::GetEnergy(Player) >= 0.5f)
					{
						Pursuit_Long_flash(Player, Enemy);
						return;
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_01(_pre|_charge)$"))) {
					float LeftSleepTime = 0.425f;
					if (regex_match(EnemyHit, regex("(female|male)_\\w+_dodge_front(_w+)*_\\d+$")))
					{
						LeftSleepTime += 0.11f;
					}
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) < 0.41f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_01(_pre|_charge)$"))) {
					float RightSleepTime = 0.665f;
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) < 0.41f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllAttack::Enemy_emptystep))/*µ–»ÀΩª’Òµ∂*/
			{
				if (GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					if (GameTool::GetEnergy(Player) < 0.5f)
					{
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							this_thread::sleep_for(chrono::milliseconds(20));
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							this_thread::sleep_for(chrono::milliseconds(20));
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						}
						const ULONG64 MaxAttackTime = GetTickCount64() + 200;
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetEnergy(Player) < 1.2f && GameTool::GetCurTimeForLogicState(Enemy) > 0 && GameTool::GetCurTimeForLogicState(Enemy) <= 0.6f && !CanHoldAttack && GameTool::GetHeroContinueLogic(Enemy) != 9)
					{
						if (GameTool::GetCurTimeForLogicState(Enemy) > 0.25f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
					else
					{
						int i = 0;
						if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
						}
						const uintptr_t MaxTime = GetTickCount64() + 800;
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, AllAttack::Enemy_dodge))
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
								i = 1;
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (i == 1)
						{
							const uintptr_t MaxTime3 = GetTickCount64() + 800;
							while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
								string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(State, regex("(female|male)_\\w+_sprint_(start|inertia)_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
								{
									i = 2;
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
								Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;

			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Spear_Left_Attack))/*≥§«π◊Ûº¸¿∂∂•*/
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.52f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.75f;
					if (regex_match(EnemyHit, regex("(female|male)_spear_sprint_attack_light_01$")))
					{
						LeftSleepTime += 0.1f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.52f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.78f;
					if (regex_match(EnemyHit, regex("(female|male)_spear_sprint_attack_light_01$")))
					{
						RightSleepTime += 0.1f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.52f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Spear_Right_Attack))/*≥§«π”“º¸º¸¿∂∂•*/
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float SleepTime = 0.58f;
					if (regex_match(EnemyHit, regex("(female|male)_spear_sprint_attack_heavy_01$")))
					{
						SleepTime += 0.07f;
					}
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					if (GameTool::GetCurTimeForLogicState(Enemy) > SleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float SleepTime = 0.68f;
					if (regex_match(EnemyHit, regex("(female|male)_spear_sprint_attack_heavy_01$")))
					{
						SleepTime += 0.06f;
					}
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					if (GameTool::GetCurTimeForLogicState(Enemy) > SleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}

				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Katana_Left_Attack))
			{
				static int Mode = 0;
				bool State = false;
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (GameTool::Get_EntityPercentage2D(Player, Enemy) > 5.f)
				{
					Mode = 1;
				}

				if (GameTool::GetEnergy(Player) >= 0.5f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_(sprint_|run_)*attack_light_01$")))
					{
						if (GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							return;
						}
					}
				}


				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Attack = 0.13f;
					float NoAttack = 0.12f;
					float SprintAttack = 0.025f;
					float disAttack = 0.05f;
					float RunDis = 0.02f;
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_sprint_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack + disAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}

					}
					if (regex_match(EnemyHit, std::regex("(female|male)_sw(_run)*_attack_light_01$")))
					{
						return;
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Attack = 0.16f;
					float NoAttack = 0.138f;
					float SprintAttack = 0.025f;
					float disAttack = 0.05f;
					float RunDis = 0.02f;
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_sprint_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack + disAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}
					}
					if (regex_match(EnemyHit, std::regex("(female|male)_sw(_run)*_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + RunDis)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}
					}
				}

				if (State)
				{
					const ULONG64 MaxAttackTime = GetTickCount64() + 200;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Katana_Right_Attack))
			{
				static int Mode = 0;
				bool State = false;
				if (GameTool::Get_EntityPercentage2D(Player, Enemy) > 5.f)
				{
					Mode = 1;
				}
				if (GameTool::GetEnergy(Player) >= 0.5f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_(sprint_|run_)*attack_heavy_01$")))
					{
						if (GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 500;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
								{
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							return;
						}
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Attack = 0.13f;
					float NoAttack = 0.137f;
					float SprintAttack = 0.025f;
					float disAttack = 0.05f;
					float RunDis = 0.02f;
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_sprint_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack + disAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}
					}
					if (regex_match(EnemyHit, std::regex("(female|male)_sw(_run)*_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + RunDis)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}

					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Attack = 0.16f;
					float NoAttack = 0.138f;
					float SprintAttack = 0.025f;
					float disAttack = 0.05f;
					float RunDis = 0.02f;
					if (regex_match(EnemyHit, std::regex("(female|male)_sw_sprint_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack + disAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + SprintAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}
					}
					if (regex_match(EnemyHit, std::regex("(female|male)_sw(_run)*_attack_light_01$")))
					{
						if (Mode == 1)
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack + RunDis)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								Mode = 0;
								State = true;
							}
						}
						else
						{
							if (GameTool::GetCurTimeForLogicState(Enemy) + Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) > Attack + (GameTool::Get_GamePing(G::GameAssembly) * 2) + NoAttack)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								}
								State = true;
							}
						}

					}
				}
				if (State)
				{
					const ULONG64 MaxAttackTime = GetTickCount64() + 200;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Sw_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.57f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.6f;
					if (regex_match(EnemyHit, regex("(female|male)_sw_sprint_attack_light_01$")))
					{
						RightSleepTime += 0.03f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Sw_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.525f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.6f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_twinblades_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.53f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.53f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_twinblades_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.53f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.6f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_nunchucks_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.54f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.59f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_nunchucks_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.54f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.59f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_dagger_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.54f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.57f;
					if (regex_match(EnemyHit, std::regex("(female|male)_dagger_sprint_attack_light_01$")))
					{
						RightSleepTime += 0.02f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_dagger_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {

					Pursuit_Long_flash(Player, Enemy);

				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.51f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.31f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_rod_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.55f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}

				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.75f;
					if (regex_match(EnemyHit, std::regex("(female|male)_rod_sprint_attack_light_01$")))
					{
						LeftSleepTime += 0.12f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.55f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.78f;
					if (regex_match(EnemyHit, std::regex("(female|male)_rod_sprint_attack_light_01$")))
					{
						RightSleepTime += 0.1f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.55f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_rod_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_light(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Lefttime = 0.36f - GameTool::Get_GamePing(G::GameAssembly);
					float LeftSleepTime = 0.65f;
					if (GameTool::GetCurTimeForLogicState(Enemy) > LeftSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Lefttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_heavy(_copy|_soul)*_0(1|2)(_pre|_charge)$"))) {
					float Righttime = 0.42f - GameTool::Get_GamePing(G::GameAssembly);
					float RightSleepTime = 0.68f;
					if (regex_match(EnemyHit, std::regex("(female|male)_rod_sprint_attack_heavy_01$")))
					{
						RightSleepTime += 0.1f;
					}
					if (GameTool::GetCurTimeForLogicState(Enemy) > RightSleepTime - GameTool::Get_GamePing(G::GameAssembly) * 2 - Righttime && GameTool::GetCurTimeForLogicState(Enemy) <= 0.4f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
					{
						if (GameTool::GetEnergy(Player) < 0.5f)
						{
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							}
							const ULONG64 MaxAttackTime = GetTickCount64() + 200;
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Blade_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.7f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}

				}
				if (GameTool::GetEnergy(Player) < 0.5f && (GameTool::Get_endureLevel(Player) == 5 || GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20) && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					int i = 1;
					if (Tool::_GetAsyncKeyState('W') >= 0) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
					}
					const uintptr_t MaxTime = GetTickCount64() + 800;
					while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(State, AllAttack::Enemy_dodge))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 1;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i == 1)
					{
						const uintptr_t MaxTime3 = GetTickCount64() + 1000;
						while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, regex("(female|male)_\\w+_sprint_(start|inertia)_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								}
								i = 2;
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (i == 2)
					{
						const uintptr_t MaxTime = GetTickCount64() + 800;
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							if (GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState('W') & 0x8000) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
									Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState('W') & 0x8000) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Blade_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.8f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{

					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}

				}
				if (GameTool::GetEnergy(Player) < 0.5f && (GameTool::Get_endureLevel(Player) == 5 || GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20) && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					int i = 1;
					if (Tool::_GetAsyncKeyState('W') >= 0) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
					}
					const uintptr_t MaxTime = GetTickCount64() + 800;
					while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(State, AllAttack::Enemy_dodge))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 1;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i == 1)
					{
						const uintptr_t MaxTime3 = GetTickCount64() + 1000;
						while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, regex("(female|male)_\\w+_sprint_(start|inertia)_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								}
								i = 2;
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (i == 2)
					{
						const uintptr_t MaxTime = GetTickCount64() + 800;
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							if (GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState('W') & 0x8000) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
									Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Saber_Left_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.7f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}

				}
				if (GameTool::GetEnergy(Player) < 0.5f && (GameTool::Get_endureLevel(Player) == 5 || GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20) && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					int i = 1;
					if (Tool::_GetAsyncKeyState('W') >= 0) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
					}
					const uintptr_t MaxTime = GetTickCount64() + 800;
					while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(State, AllAttack::Enemy_dodge))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 1;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i == 1)
					{
						const uintptr_t MaxTime3 = GetTickCount64() + 1000;
						while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, regex("(female|male)_\\w+_sprint_(start|inertia)_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								}
								i = 2;
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (i == 2)
					{
						const uintptr_t MaxTime = GetTickCount64() + 800;
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							if (GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState('W') & 0x8000) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
									Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState('W') & 0x8000) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_Saber_Right_Attack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.8f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{

					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}

				}
				if (GameTool::GetEnergy(Player) < 0.5f && (GameTool::Get_endureLevel(Player) == 5 || GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20) && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					int i = 1;
					if (Tool::_GetAsyncKeyState('W') >= 0) {
						Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
						Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
					}
					const uintptr_t MaxTime = GetTickCount64() + 800;
					while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(State, AllAttack::Enemy_dodge))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 1;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i == 1)
					{
						const uintptr_t MaxTime3 = GetTickCount64() + 1000;
						while (MaxTime3 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load()) {
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, regex("(female|male)_\\w+_sprint_(start|inertia)_\\d+.*")) || regex_match(State, regex("(female|male)_\\w+_dodge_to_sprint_\\w+_\\d+.*")))
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
								}
								i = 2;
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					if (i == 2)
					{
						const uintptr_t MaxTime = GetTickCount64() + 800;
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							if (GameTool::Get_endureLevel(Player) == 11 || GameTool::Get_endureLevel(Player) == 20)
							{
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState('W') & 0x8000) {
									Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
									Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
							}
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_All_Attack2))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) <= 0.53f && GameTool::GetCurTimeForLogicState(Enemy) >= 0.05f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.5f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}

					const ULONG64 MaxTime2 = GetTickCount64() + 500;
					while (MaxTime2 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_CrouchLightAttack2))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && GameTool::GetCurTimeForLogicState(Enemy) < 0.3f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_CrouchHeavyAttack2))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && GameTool::GetCurTimeForLogicState(Enemy) < 0.6f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_SlideAttack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && GameTool::GetCurTimeForLogicState(Enemy) < 0.8f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_GlideAttack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && GameTool::GetCurTimeForLogicState(Enemy) < 0.2f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, AllWeapon::Enemy_JumpAttack))
			{
				if (GameTool::GetEnergy(Player) >= 0.5f && GameTool::GetCurTimeForLogicState(Enemy) > 0.07f && GameTool::GetCurTimeForLogicState(Enemy) < 0.6f && !CanHoldAttack && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f && GameTool::GetHeroContinueLogic(Enemy) != 9)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 500;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw(_sprint|_run)*_attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$")))
						{
							return;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, AllAttack::Enemy_getup))
			{
				if (GameTool::GetEnergy(Player) < 0.5f && GameTool::GetCurTimeForLogicState(Enemy) >= 0.25f && GameTool::GetCurTimeForLogicState(Enemy) < 0.6f && GameTool::Get_EntityPercentage2D(Player, Enemy) <= 5.f)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(20));
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(20));
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					}
					const ULONG64 MaxAttackTime = GetTickCount64() + 200;
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_\\d+$"))) {
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (regex_match(EnemyHit, std::regex("(female|male)_\\w+_squat_\\d+$")))
			{
				if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {

					bool CC = false;
					if (Tool::_GetAsyncKeyState('C') >= 0) {
						Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
					}
					uintptr_t MaxAttackTime = GetTickCount64() + 400 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_crouch(_idle|_run)_\\d+$")))
						{
							if (Tool::_GetAsyncKeyState('C') & 0x8000) {
								Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(20));
							}
							if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							CC = true;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (CC)
					{
						if (Tool::_GetAsyncKeyState('C') >= 0) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
						}
						uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(LocalState, regex("(female|male)_\\w+_idle_\\d+$")))
							{
								if (Tool::_GetAsyncKeyState('C') & 0x8000) {
									this_thread::sleep_for(chrono::milliseconds(15));
									Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(1));
								}
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState('C') & 0x8000) {
							this_thread::sleep_for(chrono::milliseconds(15));
							Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
					}
					return;
				}
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					bool CC = false;
					if (Tool::_GetAsyncKeyState('C') >= 0) {
						Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
					}
					uintptr_t MaxAttackTime = GetTickCount64() + 400 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_crouch(_idle|_run)_\\d+$")))
						{
							if (Tool::_GetAsyncKeyState('C') & 0x8000) {
								Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(20));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							CC = true;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (CC)
					{
						uintptr_t MaxAttackTime = GetTickCount64() + 100 + (int)(GameGlobal::GamePing * 2000);
						while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
							if (!regex_match(EnemyState, regex("(female|male)_\\w+_crouch(_idle|_run)_\\d+$")))
							{
								break;
							}
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
						if (regex_match(EnemyState, std::regex("(female|male)_\\w+_dodge.*")))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_light_\\d+(_pre)*$"))) {//∂◊A
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
						else
						{
							if (Tool::_GetAsyncKeyState('C') >= 0) {
								Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
							}
							uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
							while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
							{
								string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
								if (regex_match(LocalState, regex("(female|male)_\\w+_idle_\\d+$")))
								{
									if (Tool::_GetAsyncKeyState('C') & 0x8000) {
										this_thread::sleep_for(chrono::milliseconds(15));
										Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
										this_thread::sleep_for(chrono::milliseconds(1));
									}
									break;
								}
								this_thread::sleep_for(chrono::milliseconds(1));
							}
							if (Tool::_GetAsyncKeyState('C') & 0x8000) {
								this_thread::sleep_for(chrono::milliseconds(15));
								Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(1));
							}
						}
					}
				}
				return;
			}
			else if (regex_match(EnemyHit, regex("(female|male)_\\w+_jump_inplace_up_02$")) || regex_match(EnemyHit, regex("(female|male)_\\w+_airhike_up_\\d+$")))
			{
				bool CC = false;
				if (Tool::_GetAsyncKeyState('C') >= 0) {
					Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
				}
				uintptr_t MaxAttackTime = GetTickCount64() + 400 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(LocalState, regex("(female|male)_\\w+_crouch(_idle|_run)_\\d+$")))
					{
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState('C') & 0x8000) {
							Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(20));
						}

						CC = true;
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (CC)
				{
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					uintptr_t MaxAttackTime = GetTickCount64() + 400 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_heavy_\\d+(_pre)*$")))
						{
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
				else
				{
					if (Tool::_GetAsyncKeyState('C') & 0x8000) {
						Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
						this_thread::sleep_for(chrono::milliseconds(20));
					}
				}
			}
			return;
		}
		void Parry_Attack(ULONG64 Player, ULONG64 Enemy)
		{
			int i = 0;
			bool Parry = false;
			if (GameTool::Get_EnableInputCache(Player) == 0x8808f43 && !Parry)
			{
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0)
				{
					Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				Parry = true;
			}
			if (Parry)
			{
				const ULONG64 MaxAttackTimeshock = GetTickCount64() + 300;
				while (MaxAttackTimeshock >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0)
					{
						Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					std::string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (std::regex_match(LocalState, std::regex("(female|male)_sw_attack_shock_light_01$")))
					{
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						i = 1;
						break;
					}
					else if (std::regex_match(LocalState, std::regex("(female|male)_sw_attack_shock_light_soul_01$")))
					{
						if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000)
						{
							Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000)
						{
							Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						this_thread::sleep_for(chrono::milliseconds(800));
						if (Tool::_GetAsyncKeyState(VK_SHIFT) >= 0) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), 0, 0);
						}
						const ULONG64 MaxTime = GetTickCount64() + 500 + static_cast<int>(GameGlobal::GamePing * 2000);
						while (MaxTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
						{
							string State(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
							if (regex_match(State, AllAttack::Enemy_dodge))
							{
								if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
								if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
									Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
							}
							if (regex_match(State, AllAttack::Enemy_Longdodge) || regex_match(State, AllAttack::Enemy_LongdodgeA))
							{
								if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
									Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
									this_thread::sleep_for(chrono::milliseconds(15));
								}
								return;
							}

							this_thread::sleep_for(chrono::milliseconds(1));
						}
						if (Tool::_GetAsyncKeyState(VK_SHIFT) & 0x8000) {
							Tool::_keybd_event(VK_SHIFT, MapVirtualKey(VK_SHIFT, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						return;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (i != 1)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000)
					{
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					return;
				}
				else if (i == 1)
				{
					const ULONG64 MaxAttackTime1 = GetTickCount64() + 2000;
					while (MaxAttackTime1 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						std::string EnemyState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
						if (regex_match(EnemyState, regex("(female|male)_hurt_fly(_drop|_land).*")))
						{
							if (Tool::_GetAsyncKeyState('W') >= 0) {
								Tool::_keybd_event('W', MapVirtualKey('W', 0), 0, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							i = 2;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i != 2)
					{
						return;
					}
				}
				if (i == 2)
				{
					const ULONG64 MaxAttackTime1 = GetTickCount64() + 500;
					while (MaxAttackTime1 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (Tool::_GetAsyncKeyState(VK_SPACE) >= 0) {
							Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), 0, 0);
						}
						std::string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_\\w+_up_\\d+.*")) || regex_match(LocalState, regex("(female|male)_\\w+_jump_inplace_up_\\d+")))
						{
							if (Tool::_GetAsyncKeyState(VK_SPACE) & 0x8000) {
								Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), KEYEVENTF_KEYUP, 0);
								this_thread::sleep_for(chrono::milliseconds(15));
							}
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
							}
							i = 3;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i != 3)
					{
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SPACE) & 0x8000) {
							Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						return;
					}
				}
				if (i == 3)
				{
					const ULONG64 MaxAttackTime1 = GetTickCount64() + 500;
					while (MaxAttackTime1 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						std::string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (regex_match(LocalState, regex("(female|male)_sw_jump_attack(_light)*_\\d+_pre$")))
						{
							if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
								Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							}
						}
						if (regex_match(LocalState, regex("(female|male)_\\w+_jump_attack(_light)*_\\d+$")))
						{
							i = 4;
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (i != 4)
					{
						if (Tool::_GetAsyncKeyState('W') & 0x8000) {
							Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(15));
						}
						if (Tool::_GetAsyncKeyState(VK_SPACE) & 0x8000) {
							Tool::_keybd_event(VK_SPACE, MapVirtualKey(VK_SPACE, 0), KEYEVENTF_KEYUP, 0);
							this_thread::sleep_for(chrono::milliseconds(1));
						}
						return;
					}
				}
				if (i == 4)
				{
					const ULONG64 MaxAttackTime1 = GetTickCount64() + 800;
					while (MaxAttackTime1 >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						std::string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
						if (GameTool::Get_EnableInputCache(Player) == 0x800e43 || regex_match(LocalState, regex("(female|male)_\\w+_jump_down_to_land_\\d+$")))
						{
							if (Tool::_GetAsyncKeyState('W') & 0x8000) {
								Tool::_keybd_event('W', MapVirtualKey('W', 0), KEYEVENTF_KEYUP, 0);
							}
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			return;
		}
		VOID CALLBACK Sw::InitSwLogic(uintptr_t Player, uintptr_t Enemy)
		{
			if (!AttackMode::Fixed.load())
			{
				if (AttackMode::Attackable.load()) {
					AttackMode::Attackable.store(false);
				}
				return;
			}
			if (!AttackMode::Attackable.load()) {
				AttackMode::Attackable.store(true);
			}
			AttackStack = 0;

			string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());

			if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_01_pre$"))) { //1A ∆ ÷
				AttackStack = 1;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_01_charge$"))) {//1A Ω¯¿∂
				AttackStack = 1;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_01$"))) { //1A π•ª˜
				if (GameTool::GetCurTimeForLogicState(Player) < 0.3f)
				{
					AttackStack = 2;
				}
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_02_pre$"))) {//2A ∆ ÷
				AttackStack = 3;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_02_charge$"))) { //2A Ω¯¿∂
				AttackStack = 3;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_02$"))) { //2A π•ª˜
				if (GameTool::GetCurTimeForLogicState(Player) < 0.7f)
				{
					AttackStack = 4;
				}
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_03_pre$"))) {//3A ∆ ÷
				AttackStack = 5;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_03_charge$"))) {//3A Ω¯¿∂ 
				AttackStack = 5;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack(_light|_heavy)(_copy|_soul)*_03$"))) { //3A π•ª˜
				if (GameTool::GetCurTimeForLogicState(Player) < 0.95f)
				{
					AttackStack = 6;
				}
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_(sprint_|run_)*attack_hold(_light|_heavy)(_copy|_soul)*_0[1-2]$"))) { //1∂Œ 2∂Œ –Ó¡¶π•ª˜
				if (GameTool::GetCurTimeForLogicState(Player) < 0.95f)
				{
					AttackStack = 7;
				}
			}
			else if (regex_match(LocalState, regex("(female|male)(_\\w+)_shock_\\d+.*"))) { //’Òµ∂
				AttackStack = 8;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_light_\\d+(_pre)*$"))) {//∂◊A
				AttackStack = 9;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_crouch_attack_heavy_\\d+$"))) {//…˝¡˙
				if (GameTool::GetCurTimeForLogicState(Player) < 0.6f)
				{
					AttackStack = 9;
				}
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_slide_attack_heavy_\\d+(_pre)*$"))) {
				AttackStack = 9;
			}
			else if (regex_match(LocalState, regex("(female|male)_sw_crouch_idle_\\d+$"))) { //∂◊œ¬
				AttackStack = 10;
			}
			else if (regex_match(LocalState, AllAttack::Enemy_dodge)) { //…¡±‹
				if (GameTool::GetCurTimeForLogicState(Player) < 0.15f)
				{
					AttackStack = 11;
				}
			}
			else if (regex_match(LocalState, AllWeapon::Enemy_Bounce)) {
				if (GameTool::GetCurTimeForLogicState(Player) < 0.15f)
				{
					AttackStack = 12;
				}
			}

			if (GameTool::GetEnergy(Player) > 1.3f)
			{
				Pursuit_Long_flash(Player, Enemy);
				return;
			}
			if (GameTool::Get_EntityPercentage2D(Player, Enemy) > 5.5f) {
				INT Enegy = GameTool::GetPropertyData(Memory::RPM<ULONG64>(Player + ActorModel_RuntimePropertyData)).ConsumEnergy;
				if (GameTool::GetPropertyData(Memory::RPM<ULONG64>(Player + ActorModel_RuntimePropertyData)).CurEnergy >= Enegy)
				{
					string EnemyHit(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Enemy)).str).get());
					if (!regex_match(EnemyHit, regex("(female|male)_hero_spiritsman.*")))
					{
						ULONG64 BoneMesh = Memory::RPM<ULONG64>(Enemy + ActorModel_actorVisual);
						if (BoneMesh)
						{
							Vector3 AimTargetPos = GameTool::GetBonePos(BoneMesh, 75);
							if (GameTool::WorldToScreen(&AimTargetPos))
							{
								float selfEnergy = 0.4f - ((float)GameTool::GetPropertyData(Memory::RPM<ULONG64>(Player + ActorModel_RuntimePropertyData)).CurEnergy / Enegy) * 0.1f;
								if (GameTool::GetEnergy(Player) >= selfEnergy && GameTool::GetEnergy(Enemy) <= 1.3f)
								{
									Pursuit_Long_flash(Player, Enemy);
									return;
								}
							}
						}
					}
				}
			}
			if (AttackStack == 0)
			{
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) >= 0 && Tool::_GetAsyncKeyState(VK_RBUTTON) >= 0) {
					Tool::_mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				}
				return;
			}
			if (AttackStack == 1 || AttackStack == 3 || AttackStack == 5) {
				Start_Attack(Player, Enemy);
				return;
			}
			else if (AttackStack == 2)
			{
				One_Attack(Player, Enemy);
				return;
			}
			else if (AttackStack == 4 || AttackStack == 6)
			{
				Two_Attack(Player, Enemy);
				return;
			}
			else if (AttackStack == 7)
			{
				if (GameTool::Get_EnableInputCache(Player) == 0x1c102)
				{
					Pursuit_Long_flash(Player, Enemy);
				}
				return;
			}
			else if (AttackStack == 8)
			{
				Parry_Attack(Player, Enemy);
				return;
			}
			else if (AttackStack == 9)
			{
				Crouch_heavy_Attack(Player, Enemy);
				return;
			}
			else if (AttackStack == 10)
			{
				if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
					this_thread::sleep_for(chrono::milliseconds(1));
					Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
					this_thread::sleep_for(chrono::milliseconds(1));
					Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (Tool::_GetAsyncKeyState('C') & 0x8000) {
					this_thread::sleep_for(chrono::milliseconds(1));
					Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
					this_thread::sleep_for(chrono::milliseconds(15));
				}

				if (Tool::_GetAsyncKeyState('C') >= 0) {
					Tool::_keybd_event('C', MapVirtualKey('C', 0), 0, 0);
				}
				uintptr_t MaxAttackTime = GetTickCount64() + 600 + (int)(GameGlobal::GamePing * 2000);
				while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
				{
					string LocalState(Tool::UnicodeToAnsi(Memory::RPM<Xstring>(GameTool::GetTrueRuntimeEventTrackInfo(Player)).str).get());
					if (regex_match(LocalState, regex("(female|male)_\\w+_idle_\\d+$")))
					{
						break;
					}
					this_thread::sleep_for(chrono::milliseconds(1));
				}
				if (Tool::_GetAsyncKeyState('C') & 0x8000) {
					this_thread::sleep_for(chrono::milliseconds(1));
					Tool::_keybd_event('C', MapVirtualKey('C', 0), KEYEVENTF_KEYUP, 0);
					this_thread::sleep_for(chrono::milliseconds(30));
				}
			}
			else if (AttackStack == 11)
			{
				if (GameTool::GetCurTimeForLogicState(Player) <= 0.02f && GameTool::GetCurTimeForLogicState(Player) >= 0.01f)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(15));
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(15));
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(15));
					}
					uintptr_t MaxAttackTime = GetTickCount64() + 100 + (int)(GameGlobal::GamePing * 2000);
					while (MaxAttackTime >= GetTickCount64() && AttackMode::Attackable.load() && AttackMode::Fixed.load())
					{
						if (GameTool::Get_EnableInputCache(Player) == 0x2808f43)
						{
							break;
						}
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			else if (AttackStack == 12)
			{
				if (GameTool::GetCurTimeForLogicState(Player) <= 0.05f && GameTool::GetCurTimeForLogicState(Player) >= 0.01f)
				{
					if (Tool::_GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(1));
						Tool::_mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
					if (Tool::_GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
						this_thread::sleep_for(chrono::milliseconds(1));
						Tool::_mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
						this_thread::sleep_for(chrono::milliseconds(1));
					}
				}
			}
			return;
		}
	}
}