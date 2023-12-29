struct Global_Variables_Structure
{
	__int8 Additional_Bytes[12];

	float Current_Time;

	float Frame_Time;

	__int32 Maximum_Clients;

	__int32 Tick_Number;

	float Interval_Per_Tick;
};

struct __attribute__((packed)) Player_Data_Structure
{
	__int8 Priority;

	__int32 Memory_Tolerance;

	__int32 Tolerance;

	__int32 Shots_Fired;

	float Memorized_Y;
};

Player_Data_Structure Players_Data[64];

void Get_Priorities()
{
	__int32 Entity_Number = 1;

	Traverse_Entity_List_Label:
	{
		using Get_Name_Type = void(__thiscall*)(void* Engine, __int32 Number, char* Name);

		char Name[132];

		Get_Name_Type(537018208)((void*)540435380, Entity_Number, Name);

		if (Name[0] != 0)
		{
			wprintf(L"[ ? ] \"%hs\" %i %i\n", Name, Entity_Number, Players_Data[Entity_Number - 1].Priority);
		}

		if (Entity_Number < (*(Global_Variables_Structure**)607726732)->Maximum_Clients)
		{
			Entity_Number += 1;

			goto Traverse_Entity_List_Label;
		}
	}
}

void Set_Priority(Interface_Structure* Console_Variable)
{
	__int32 Player_Number = atoi(Console_Variable->String);

	Players_Data[Player_Number - 1].Priority = atoi((char*)((unsigned __int32)Console_Variable->String + 3 - (Player_Number < 10)));
}