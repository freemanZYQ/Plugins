#include "hookutils.h"
#include <string>
/*
 * getHealth():
 int attributeMap=*(int *)(a1+0xBDC);  //需对新版本做调整
int AttributeAdd= old_ABMgetInstance(attributeMap,attribute);

* (float *)(AttributeAdd+76)=0;    //gethealth原函数中找
addItem(int itemId,int itemCount)函数中int Inventory=*(int *)(bl_localplayer + 3488);的查找方法:
找到原so中对_ZNK9Inventory15getSelectedSlotEv函数的调用

getContainerItem()函数中FillingContainer的查找方法:
从原SO中找到_ZN6Player11hasResourceEi.

PlayerSetFlying()查找方法:
找到原so中对_ZNK9Abilities8isFlyingEv函数的引用.传入+1


ABMgetInstance()中 char * name=*(int *)(a2+16);的查找方法:

_ZNK9Attribute7getNameEv中找
int LocalPlayermove(int a1,int a2) 中坐标对应关系
_ZN6Entity4moveERK4Vec3中找到"random.swim"字符串
 *
 * */
using namespace std;
static int lockLevel = 0;
static int lockDay= 0;
static int lockTime = 3;
static int lockTime2 = 0;
static int lockRain = 0;
static int lockLightning = 0;
static int lockJump = 0;
static int lockMode = 3;
static int lockFly = 1;
static int lockInventory = 0;
static int lockView = 1;
static int lockDistance = 14;

static int lockArmor = 0;
static int lockHealth = 0;
static int lockUseItem = 0;
static int lockInvi = 0;
static int lockDing = 0;

/**
 * 物品添加控制
 * */
int containerdrop=0;
int baseA=0;
static float worldX=-1;
static float worldY=-1;
static float worldZ=-1;
float targetWorldX=-10000;
float targetWorldY=-10000;
float targetWorldZ=-10000;
int delivery=0;
int Inventoryponit=0;
int ItemInstancepoint=0;
int bl_minecraft = 0;
int bl_localplayer=0;
int bl_level = 0;

int iskill=0;
int testSprintin=0;
int gameModeSet=0;
int currentTargetHealth=0;
int maxTargetHealth=0;
int playerisFlying=0;
//getGui
int (*old_getGui)(int a1)=NULL;
int (*old_ItemInstance)(int a1)=NULL;
int (*old_ItemInstance3)(int id,int amount,int damage)=NULL;
int (*old_getid)(int r0) = NULL;
int (*old_getCustomName)(int r0,int r1) = NULL;
int (*old_FillingContainergetItem)(int a1,int a2) = NULL;

int (*old_Inventoryload)(int r0,int r1) = NULL;
int (*old_MinecraftgetLevel)(int a1) = NULL;
int (*old_MinecraftClientgetLocalPlayer)(int a1) = NULL;
int (*old_MinecraftClientgetServer)(int a1) = NULL;
int (*old_showTipMessage)(int a1,char *a2) = NULL;
int (*old_setGameType)(int a1,int a2) = NULL;
int (*old_getLevelData)(int a1) = NULL;
int (*old_setGameMode)(int a1,int a2) = NULL;
int (*old_setSprinting)(int r0,int r1) = NULL;
int (*old_getStatusFlag)(int r0,int r1) = NULL;
int (*old_BaseAttributeMapgetInstance)(int r0,int r1) = NULL;
int (*old_getMaxHealth)(int r0) = NULL;
int (*old_EntitygetName)(int r0) = NULL;
int (*old_setItem)(int r0,int r1) = NULL;
int (*old_InventoryclearSlot)(int r0,int r1) = NULL;
int (*old_Inventory3add)(int a1,int a2,int a3) = NULL;
int (*old_getGameType)(int a1) = NULL;
int (*old_getGameMode)(int a1) = NULL;
int (*old_MinecraftIsInGame)(int a1) = NULL;
int (*old_getContainerSize)(int r0) = NULL;
int (*old_getSeed)(int r0) = NULL;


/*int getLocalPlayer(){
	if(bl_minecraft){
		return old_MinecraftIsInGame(bl_minecraft);
	}else{
		return 0;
	}
}*/

int  MinecraftClientgetServer(int a1) {
	int ret=old_MinecraftClientgetServer(a1);
//	if(bl_localplayer==0){
		bl_level=	old_MinecraftgetLevel(ret);
		bl_localplayer=old_MinecraftClientgetLocalPlayer(a1);
		bl_minecraft=a1;
	/*LogD("<%s> bl_minecraft=%d ", __FUNCTION__, bl_minecraft);
	LogD("<%s> bl_localplayer=%d ", __FUNCTION__, bl_localplayer);*/
	//}
	return ret;
}

int isPlayerFlying(){
	if(bl_localplayer){
	 bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
	if(bl_minecraft){
		bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
	}
	int result = bl_localplayer;
	  if ( bl_localplayer ){
	  //  result = *(unsigned char *)(bl_localplayer + 3309);
	    result = *(unsigned char *)(bl_localplayer + 3317);
	  }
	  return result;
}
}
 void PlayerSetFlying(int r0){
	 if(bl_minecraft){
	 bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
	 //bl_localplayer
	  if ( bl_localplayer ){
		  *(unsigned char *)(bl_localplayer + 3317)=r0;
		  *(unsigned char *)(bl_localplayer + 3318)=r0;
		  int result = *(unsigned char *)(bl_localplayer + 3317);
	  }
	  	  }
}

int Inventoryload(int r0,int r1) {
	Inventoryponit=r0;
	return old_Inventoryload(r0,r1);

}

/*int setItem(int r0,int r1) {
	// LogD("<%s> r0=%d", __FUNCTION__,r0);g
	return old_setItem(r0,r1);

}*/

float moveSpeed;

void doRoleCheat(int flag,int arg1,int arg2){
	switch(flag){
		   case 2:{
			   moveSpeed=arg2*0.1;
			   break;
		   }
		   default:{
			   break;
		   }
		}
}



/*int (*old_Inventory3add)(int a1,int a2,int a3) = NULL;
int Inventory3add(int a1,int a2,int a3) {
	 int ret= old_Inventory3add(a1,a2,a3);
	return ret;
}*/

/*
 * 还未用到
 */
//int (*old_setUserData)(int a1, int a2,int a3) = NULL;
int ItemInstance3(int a1, int a2,int a3) {
	if(ItemInstancepoint==0){
	 ItemInstancepoint=a1;
	}
	return old_ItemInstance3(a1,a2,a3);
}
 int  bl_setItemInstance(int a1, int itemId, char itemCount, int damage)
{
  int v4; // r6@1
  int v5; // r4@1
  *(int *)(a1 + 2) = damage;
  v4 = itemId;
  *(unsigned char *)a1 = itemCount;
   v5 = a1;
  return old_setItem(v5, v4);
}
 int newarray = operator new(0x14);
 int  bl_newItemInstance(int itemId, char itemCount, int damage)
{
  *(int *)(newarray + 8) = 0;
  bl_setItemInstance(newarray, itemId, itemCount, damage);
  return newarray;
}
void addItem(int itemId,int itemCount,int damage) {
	 //	LogD("<%s> damage=%d ", __FUNCTION__, damage);
		// old_ItemInstance(ItemInstancepoint);
	if(bl_minecraft){
	bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
		int iteminstan=  bl_newItemInstance(itemId,itemCount,damage);
		//int Inventory=*(int *)(bl_localplayer + 3480);
		int Inventory=*(int *)(bl_localplayer + 3488);
		old_Inventory3add(Inventory, iteminstan, 1);//这里的1是布尔类型
	}
	 //LogD("<%s> itemCount=%d r0=%s ", __FUNCTION__,itemCount, "new添加成功");
}
//获取仓库物品
int getContainerItem(int slotid){
	int *slotinfo=new int[2];

	if ( !bl_minecraft ){
	 return slotinfo;
	}
	bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
	int FillingContainer=*((int *)bl_localplayer + 872);
	  int item = old_FillingContainergetItem(FillingContainer, slotid); //i表示第几个格
	  if(item){
	  int id=	old_getid(item);
	  int count= *(unsigned char *)(item);
	  int sid=*(unsigned char *)(item+2);
	//  LogD("<%s> id=%d count=%d sid=%d", __FUNCTION__,id,count,sid);
	  slotinfo[0]=id;
	  slotinfo[1]=count;
	  return slotinfo;
	  }else{
	  return slotinfo;
	  }
}
//获取仓库大小
int getContainerSize(){
	if(bl_minecraft){
	bl_localplayer= old_MinecraftClientgetLocalPlayer(bl_minecraft);
	if(bl_localplayer){
	int Inventory=*(int *)(bl_localplayer + 3488);
	int size=old_getContainerSize(Inventory);

	}
	}
	return 0;
}

int getMyWorldSeed(){
	 if(!bl_minecraft){
		return 0;
	}
int mcf = old_MinecraftClientgetServer(bl_minecraft);
	if(!mcf){
		return 0;
	}
 	bl_level=	old_MinecraftgetLevel(mcf);
	if(!bl_level){
	return 0;
	}
 	int bll=old_getLevelData(bl_level);
	//int gameType=old_getGameType(bll);
	if(!bll){
		return 0;
	}
 	int ret=old_getSeed(bll);
	return ret;
}
int IsInGame(){
	if(!bl_minecraft){
		return 0;
	}
		int ret=old_MinecraftIsInGame(bl_minecraft);
		if(!ret){

		if(getMyWorldSeed()==0){
			return 0;
		}
		return 1;
		}else{
	   return 1;
		}

}
/*
 *坐标
 */
float doCallbackGetX(){
	return worldX;
}
float doCallbackGetY(){
	return worldY;
}
float doCallbackGetZ(){
	return worldZ;
}
void doCheatPostXYZ(float arg0,float arg1,float arg2){
	targetWorldX = arg0;
	targetWorldY = arg1;
	targetWorldZ = arg2;

}



/*
 * UI控制逻辑
 */
void doProcessCheat(int flag, int arg1, int arg2) {
	if (flag == 1) {
		lockLevel = arg2;//级别
	} else if (flag == 2) {
		lockHealth = arg2;//无敌
	} else if (flag == 3) {
		lockTime = arg2;//时间
	} else if (flag == 4) {
		lockRain = arg2;//雨雪
	} else if (flag == 5) {
		lockView = arg2;//视角
	} else if (flag == 11) {
		lockTime2 = arg2;//时间锁定
	} else if (flag == 12) {

	} else if (flag == 13) {
		lockUseItem = arg2;//使用物品
	} else if (flag == 14) {
		lockDing = arg2;//动物移动
	} else if (flag == 15) {
//		addItem();
		delivery = 1;
	}else if (flag = 16) {
//		LogD("<%s> arg2=%d", __FUNCTION__,arg2);
		PlayerSetFlying(arg2);//飞行
		playerisFlying=arg2;
      //LogD("<%s> iseed=%d", __FUNCTION__, getMyWorldSeed());
      //LogD("<%s> getlocalplayer=%d", __FUNCTION__,  getLocalPlayer());
	/*	for(int i=0;i<52;i++){
		  int *item=getContainerItem(i);
		}*/
		 //LogD("<%s> item[0]=%d item[1]=%d", __FUNCTION__, item[0], item[1]);


	}else if (flag = 18) {
//		iskill = arg2; 	//自杀
	}
}
void doAddItemCheat(int flag,int itemId,int itemCount,int damage){
	//LogD("<%s> arg1=%d arg2=%d", __FUNCTION__,arg1,arg2);
	 addItem(itemId,itemCount,damage);
}
static int screenshot = 0;
jclass sshelper = NULL;
jmethodID method1 = NULL;
static JavaVM *gs_jvm = NULL;
void getscreen() {
	JNIEnv *screen_env;
	if (gs_jvm->GetEnv((void**) &screen_env, JNI_VERSION_1_4) != JNI_OK) {
		int status = gs_jvm->AttachCurrentThread((void **) &screen_env, NULL);
		if (status < 0) {
			return NULL;
		}
	}
	if (screen_env) {
		if (sshelper == 0) {
			sshelper = screen_env->FindClass(
					"com/gameassist/plugin/nativeutils/ScreenshotHelper");
		}
		if (sshelper == 0) {
			return;
		}
		if (method1 == 0) {
			method1 = screen_env->GetStaticMethodID(sshelper, "takeScreenshot",
					"()V");
		}
		if (method1 == 0) {
			return;
		}
		if (screenshot == 0) {
			screenshot = 1;
		} else {
			screen_env->CallStaticVoidMethod(sshelper, method1, NULL);
		}
	}
}
int (*old_MinecraftClientupdate)(int a1) = NULL;
int MinecraftClientupdate(int a1) {
	int ret = old_MinecraftClientupdate(a1);
	if (screenshot == 1) {
		//LogD("<%s> ret=%d", __FUNCTION__, ret);
		getscreen();
		screenshot = 0;
	}
	return ret;
}
void doScreenshotCheat(JNIEnv *env,JavaVM* vm) {
	 gs_jvm=vm;
	 getscreen();
}
int (*old_setTime)(int r0, int r1) = NULL;
int setTime(int r0, int r1) {
		if(lockTime == 0){
			if(lockTime2==0){
				lockTime = 3;
			}
			return old_setTime(r0,1000);
		}
		if(lockTime ==1){
			if(lockTime2==0){
				lockTime = 3;
			}
			return old_setTime(r0,36666);
		}
		if(lockTime == 2){
			if(lockTime2==0){
				lockTime = 3;
			}
			return old_setTime(r0,62000);
		}
		return old_setTime(r0,r1);

}
int (*old_getPlayerLevel)(int r0) = NULL;
int getPlayerLevel(int r0) {
	return lockLevel;
}
int (*old_getSky)(int r0) = NULL;
int getSky(int r0) {
//		LogD("<%s> r0=%d old=%f old=%f", __FUNCTION__, r0, *(float *)(r0 + 32),*(float *)(r0 + 44));
//		*(float *)(r0 + 32) = 1.0;//雨雪
//		*(float *)(r0 + 44) = 1.0;//闪电
//		*(float *)(r0 + 48) = 1.0;//48  雾霾
	if (lockRain == 0) {
		*(float *) (r0 + 32) = 0;
		lockRain = 3;
	} else if (lockRain == 1) {
		*(float *) (r0 + 32) = 1.0;
		lockRain = 3;
	} else if (lockRain == 2) {
		*(float *) (r0 + 32) = 2.0;
		lockRain = 3;
	}

	if (lockLightning == 0) {
		*(float *) (r0 + 48) = 0;
		lockLightning = 3;
	} else if (lockLightning == 1) {
		*(float *) (r0 + 48) = 1.0;
		lockLightning = 3;
	} else if (lockLightning == 2) {
		*(float *) (r0 + 48) = 2.0;
		lockLightning = 3;
	}
	return old_getSky(r0);
}
int (*old_option)(int r0) = NULL;
int option(int r0) {
	*((unsigned char *)r0 + 140) = lockView;
//	LogD("<%s> 140=%d", __FUNCTION__, *((int*)r0 + 35));
//	LogD("<%s> r0=%d old=%d", __FUNCTION__, r0,old_option(r0));
	return old_option(r0);
}

int (*old_getArmorValue)(int r0, int r1) = NULL;
int getArmorValue(int r0, int r1) {
	if(lockArmor){
		return 100;
	}
	return old_getArmorValue(r0,r1);
}
int (*old_useItem2)(int r0, int r1) = NULL;
int useItem2(int r0, int r1) {
		*(int *)(r0 + 3311) =1;
	return old_useItem2(r0,r1);
}
int (*old_setSpeed)(int r0, float r1) = NULL;
int setSpeed(int r0, float r1) {
	if(lockDing){
		return old_setSpeed(r0,0);
	}
	return old_setSpeed(r0,r1);
}

int (*old_addPotion)(int r0) = NULL;
int addPotion(int r0) {
	return old_addPotion(r0);

}
int getGameCurrentMode(){
	if(bl_level&&bl_minecraft){

	int bll=old_getLevelData(bl_level);
	int gameType=old_getGameType(bll);
	//LogD("<%s> gameType=%d", __FUNCTION__, gameType);
	/*int gameMode=old_getGameMode(bl_minecraft);
	LogD("<%s> gameType=%d gameMode=%d", __FUNCTION__, gameType,gameMode);*/
	return gameType;
	}
}

void changeMode(int a1){
	//生存模式a1=0
	//创造模式a1=1
//	getGameCurrentMode();
	 	if(bl_level&&bl_minecraft){
			int bll=old_getLevelData(bl_level);
			old_setGameType(bll, a1);
			old_setGameMode(bl_minecraft,a1);
		}else{
//			LogD("<%s> r0=%s ", __FUNCTION__, "bl_level is NULL!");
		}
}

void doGameCheat(int flag,int arg1,int arg2){
	switch(flag){
	   case 1:{
		   changeMode(arg2);
		   break;
	   }
	   case 18:{
		   iskill = arg2;
		   break;
	   }
	   case 2:{
		   containerdrop = arg2;
		   break;
	   }
	   default:{
		   break;
	   }
	}
}

int (*old_respawn)(int r0) = NULL;
int respawn(int r0) {
	return old_respawn(r0);
}
int (*old_getAttackDamage)(int r0) = NULL;
int getAttackDamage(int r0) {
	return 7;

}

int killcontr=0;
int attribute=0;
int (*old_ABMgetInstance)(int a1,int a2) = NULL;
int ABMgetInstance(int a1,int a2) {
	int ret = old_ABMgetInstance(a1, a2);
	  char * name=*(int *)(a2+16);
	 if(name&&attribute==0){
	if(strstr(name,"generic.health")!=NULL){
		//LogD("<%s> name=%s", __FUNCTION__, name);
		attribute=a2;
	}
	 }
	/*if (iskill) {
		int aa = *(int *) (ret + 76);
		if (aa == 0 && killcontr > 3) {
//			LogD("<%s> ret=%d", __FUNCTION__, aa);
			iskill = 0;
		}
		killcontr++;
		*(int *) (ret + 76) = 0;
	}*/
	return ret;
}


float (*old_setDefaultValue)(int a1,float a2,int a3) = NULL;
float setDefaultValue(int a1,float a2,int a3) {
	if(a3==2){
		if(moveSpeed!=0){
			a2=(float)moveSpeed;
			}
		}
		return old_setDefaultValue(a1,a2,a3);
}



int (*old_LocalPlayermove)(int a1,int a2) = NULL;
int LocalPlayermove(int a1,int a2) {
	/*worldX=*(float *)(((float *)a2+24));//原坐标
	worldZ=	*(float *)(((float *)a2+26));
	worldY=*(float *)(((float *)a2+25));*/
	   worldX=*(float *)(((float *)a2+24+1));//原坐标
		worldZ=	*(float *)(((float *)a2+26+1));
		worldY=*(float *)(((float *)a2+25+1));
//	 LogD("<%s>X=%f Y=%f Z=%f", __FUNCTION__,worldX,worldY,worldZ);
	if( targetWorldX>-10000&&targetWorldY>-10000&&targetWorldZ>-10000){

		//LOX坐标
		 	/**(float *)(((float *)a1+2))=1869.5;
			*(float *)(((float *)a1+5))=1869.5;
			*(float *)(((float *)a1+8))=1869.5;*/

			 *(float *)(((float *)a2+24+1))=targetWorldX;//原坐标
			*(float *)(((float *)a2+27+1))=targetWorldX+0.1;//目的坐标

       //z坐标
			/* *(float *)(((float *)a1 + 4))=320.5;
			*(float *)(((float *)a1 + 7))=320.5;
			*(float *)(((float *)a1 + 10))=320.5;*/

			 *(float *)(((float *)a2+26+1))=targetWorldZ;
			*(float *)(((float *)a2+29+1))=targetWorldZ+0.1;

			//y坐标
		/*	 *(float *)(((float *)a1 + 3))=77.62;
			*(float *)(((float *)a1 + 6))=77.62;
			*(float *)(((float *)a1 + 9))=77.62;*/

			*(float *)(((float *)a2+25+1))=targetWorldY;
			*(float *)(((float *)a2+28+1))=targetWorldY+0.1;
			targetWorldX=-10000;
			targetWorldY=-10000;
			targetWorldZ=-10000;
		}
//   LogD("<%s>X=%f Y=%f Z=%f", __FUNCTION__,worldX,worldY,worldZ);
	int ret=old_LocalPlayermove(a1,a2);
	return ret;
}
int (*old_isPlayer)(int a1) = NULL;
int (*old_getHealth)(int a1) = NULL;
int getHealth(int a1) {
	int isplayer=old_isPlayer(a1);
	if(isplayer==1){
	   if(attribute!=0){
	   // int attributeMap=*(int *)(a1+0xBCC);    //0.14.0
	    int attributeMap=*(int *)(a1+0xBDC);
		int AttributeAdd= old_ABMgetInstance(attributeMap,attribute);
		//int starthealth=*(float *)(AttributeAdd+76);
		if(iskill==1){
		* (float *)(AttributeAdd+76)=0;    //gethealth原函数中找
		iskill=0;
		}
		if(lockHealth==1){
			if(old_getHealth(a1)!=0){
			//int maxhealth=old_getMaxHealth(a1);
		 *(float *)(AttributeAdd+76)=(float)100;
			}
		}
	   }
 	}
	int ret=old_getHealth(a1);
	return ret;
}

int (*old_setLastHurtMob)(int a1,int a2) = NULL;
int setLastHurtMob(int a1,int a2) {
	int temp=0;
	   if(!old_isPlayer(a1)){
		 temp=a1;
	   }else{
		  temp=a2;
	   }
	   if(temp){
		currentTargetHealth=getHealth(temp);
		maxTargetHealth=old_getMaxHealth(temp);
	   }

	   int ret= old_setLastHurtMob(a1,a2);
       if(!old_isPlayer(a1)){
       		 temp=a1;
       	   }else{
       		  temp=a2;
       	   }
       	   if(temp){
       		currentTargetHealth=getHealth(temp);
       		maxTargetHealth=old_getMaxHealth(temp);
       	   }

		return ret;
}
int (*old_getTarget)(int a1) = NULL;
int getTarget(int a1) {
	int ret=old_getTarget(a1);
	//LogD("<%s>ret=%d", __FUNCTION__, ret);
	 if(ret){
		 if(!old_isPlayer(a1)){
			 currentTargetHealth = getHealth(a1);
			 maxTargetHealth= old_getMaxHealth(a1);
			 /*float x=*(float *)(((float *)a1+24));//原坐标
			 float z=	*(float *)(((float *)a1+26));
			float y =*(float *)(((float *)a1+25));*/
		//	LogD("<%s>X=%f Y=%f Z=%f", __FUNCTION__,x,z,y);
		 }else{
			 currentTargetHealth = 0;
			 maxTargetHealth= 0;
		 }
		// LogD("<%s>isPlayercurrentTargetHealth=%d isPlayermaxTargetHealth=%d", __FUNCTION__, currentTargetHealth, maxTargetHealth);
		// math.sqrt((x1-x2)* (x1-x2)+ (y1-y2)* (y1-y2)+ (z1-z2)* (z1-z2));
		 /*else{
		 currentTargetHealth = getHealth(ret);
		maxTargetHealth= old_getMaxHealth(ret);
		 LogD("<%s>currentTargetHealth=%d maxTargetHealth=%d", __FUNCTION__, currentTargetHealth, maxTargetHealth);
		 }*/
		 /*char *name=*(char *)old_EntitygetName(ret);
		 LogD("<%s>name=%s", __FUNCTION__, name);*/

	}
	return ret;
}
int (*old_getNavigation)(int a1) = NULL;
int getNavigation(int a1) {
	int ret=old_getNavigation(a1);

	if(ret){
		 if(!old_isPlayer(a1)){
			 currentTargetHealth = getHealth(a1);
			 maxTargetHealth= old_getMaxHealth(a1);
		 }else{
			 currentTargetHealth = 0;
			 maxTargetHealth= 0;
		 }
		// LogD("<%s>isPlayercurrentTargetHealth=%d isPlayermaxTargetHealth=%d", __FUNCTION__, currentTargetHealth, maxTargetHealth);
	}
		return ret;
}
int (*old_DamageSourcei)(int a1,int a2,int a3) = NULL;
int DamageSourcei(int a1,int a2,int a3) {
	if(old_isPlayer(a1)&&lockHealth==1){
		return 0;
	}
	int ret=old_DamageSourcei(a1,a2,a3);
		return ret;
}

int (*old_clearSlot)(int a1,int a2) = NULL;
int clearSlot(int a1,int a2) {
	//LogD("<%s>a1=%d a2=%d", __FUNCTION__, a1,a2);
	int ret=old_clearSlot(a1,a2);
	// LogD("<%s>ret=%d", __FUNCTION__, ret);
		return ret;
}
int (*old_FillingContainerdropAll)(int a1,int a2,int a3,int a4) = NULL;
int FillingContainerdropAll(int a1,int a2,int a3,int a4) {
	//LogD("<%s>a1=%d a2=%d a3=%d a4=%d", __FUNCTION__, a1,a2,a3,a4);
   /*
    * =1不掉落
    */
	if(containerdrop==1){
		return a1;
	}else{
		return old_FillingContainerdropAll(a1,a2,a3,a4);
	}
}
 int (*old_addCreativeItem)(int a1,int a2) = NULL;
int addCreativeItem(int a1,int a2) {
	int ret=old_addCreativeItem(a1,a2);
//	LogD("<%s>ret=%d", __FUNCTION__, ret);

}
/*int (*old_getSeed)(int a1) = NULL;
int getSeed(int a1) {
	int ret=old_getSeed(a1);
 LogD("<%s>ret=%d", __FUNCTION__, ret);

}*/
const static HOOK_SYMBOL gHookSymbols[] = {
		//{"_ZN6Player6isHurtEv", (void *)&isHurt, (void **)&old_isHurt},//无敌
		//		{"_ZNK6Player7useItemER12ItemInstance", (void *)&useItem2, (void **)&old_useItem2}, //物品使用不会减少
		//{"_ZN3Mob12setInvisibleEb", (void *)&setInvisible, (void **)&old_setInvisible},  // 设置隐身
		//	{"_ZN12ItemInstance8_setItemEi", (void *)&setItem,      (void **)&old_setItem},  //类型参数 _ZN9Inventory4loadERK7ListTag
		//{"_ZN9Inventory3addER12ItemInstanceb", (void *)&Inventory3add,      (void **)&old_Inventory3add},
		//  {"_ZN16FillingContainer12_addResourceERK12ItemInstance", (void *)&Inventory3add,      (void **)&old_Inventory3add},
		//{"_ZNK9Inventory16getContainerSizeEv", (void *)&getContainerSize,      (void **)&old_getContainerSize},

        //{"_ZN8GameMode6attackER6PlayerR6Entity", (void *)&GameModeattac,      (void **)&old_GameModeattac},
   // {"_ZN3Mob14setLastHurtMobEP6Entity", (void *)&setLastHurtMob,      (void **)&old_setLastHurtMob},  //显示攻击状态下血量
        //{"_ZN6Player6isHurtEv", (void *)&PlayerisHurt,      (void **)&old_PlayerisHurt},
	     //   {"_ZN3Mob13getNavigationEv", (void *)&getNavigation,      (void **)&old_getNavigation},
{"_ZNK6Player14getPlayerLevelEv", (void *)&getPlayerLevel, (void **)&old_getPlayerLevel}, //级别
{"_ZN5Level7setTimeEi", (void *)&setTime, (void **)&old_setTime},  //时间
{"_ZNK7Weather15getSkyFlashTimeEv", (void *)&getSky, (void **)&old_getSky},//天气   雨天,闪电
{"_ZNK7Options8isFlyingEv", (void *)&option, (void **)&old_option},    //视角
{"_ZN3Mob13getArmorValueEv", (void *)&getArmorValue, (void **)&old_getArmorValue},  // 护甲值100
{"_ZN3Mob8setSpeedEf", (void *)&setSpeed, (void **)&old_setSpeed},  // 动物的移动速度     player mob speed 都试过,原地不动,跳着走
{"_ZN9Inventory15getAttackDamageEv", (void *)&getAttackDamage, (void **)&old_getAttackDamage},  //伤害
{"_ZN9Inventory4loadERK7ListTag", (void *)&Inventoryload,      (void **)&old_Inventoryload},  //类型参数 _ZN9Inventory4loadERK7ListTag
{"_ZN12ItemInstanceC2EPK4Itemi", (void *)&ItemInstance3,      (void **)&old_ItemInstance3}, //获取Item实例
{"_ZN15MinecraftClient9getServerEv", (void *)&MinecraftClientgetServer,      (void **)&old_MinecraftClientgetServer},
{"_ZN11LocalPlayer4moveERK4Vec3", (void *)&LocalPlayermove,      (void **)&old_LocalPlayermove},
{"_ZNK16BaseAttributeMap11getInstanceERK9Attribute", (void *)&ABMgetInstance,      (void **)&old_ABMgetInstance},//获取attribute的值
{"_ZN17AttributeInstance15setDefaultValueEfi", (void *)&setDefaultValue,      (void **)&old_setDefaultValue}, //设置行走速度
{"_ZN15MinecraftClient6updateEv", (void *)&MinecraftClientupdate,      (void **)&old_MinecraftClientupdate}, //截屏
{"_ZNK3Mob9getHealthEv", (void *)&getHealth,      (void **)&old_getHealth},//设置自杀及无敌
{"_ZN3Mob4hurtERK18EntityDamageSourcei", (void *)&DamageSourcei,      (void **)&old_DamageSourcei}, //无敌,不接受生物攻击
{"_ZN3Mob9getTargetEv", (void *)&getTarget,      (void **)&old_getTarget},  //被怪物攻击时显示动物血量
{"_ZN16FillingContainer7dropAllEiib", (void *)&FillingContainerdropAll,      (void **)&old_FillingContainerdropAll}, //物品不掉落
{"_ZN9Inventory9clearSlotEi", (void *)&clearSlot,      (void **)&old_clearSlot},  //删除背包物品
{"_ZN4Item15addCreativeItemERK12ItemInstance", (void *)&addCreativeItem,      (void **)&old_addCreativeItem},  //添加生物
};

const static FIND_SYMBOL gFindSymbols[] = {
		{"_ZN15MinecraftClient8isInGameEv",      (void **)&old_MinecraftIsInGame},
		{"_ZN12ItemInstanceC2Ev",      (void **)&old_ItemInstance},
    	{"_ZNK12ItemInstance5getIdEv",      (void **)&old_getid},
    	{"_ZNK12ItemInstance13getCustomNameEv",      (void **)&old_getCustomName},
    	{"_ZNK9Inventory16getContainerSizeEv",   (void **)&old_getContainerSize},
    	{"_ZNK16FillingContainer7getItemEi",  (void **)&old_FillingContainergetItem},  //dump 背包
    	{"_ZN15MinecraftClient14getLocalPlayerEv",      (void **)&old_MinecraftClientgetLocalPlayer},
		{"_ZNK15MinecraftClient6getGuiEv",      (void **)&old_getGui},
		{"_ZN3Gui14showTipMessageERKSs",      (void **)&old_showTipMessage},
		{"_ZN9Minecraft8getLevelEv",      (void **)&old_MinecraftgetLevel},
		{"_ZN9LevelData11setGameTypeE8GameType",      (void **)&old_setGameType},
		{"_ZN5Level12getLevelDataEv",      (void **)&old_getLevelData}, //old_getLevelData
		{"_ZN15MinecraftClient11setGameModeE8GameType",      (void **)&old_setGameMode},
		{"_ZN3Mob12setSprintingEb",      (void **)&old_setSprinting},
		{"_ZNK6Entity13getStatusFlagEi",      (void **)&old_getStatusFlag},
		 {"_ZN15EntityClassTree8isPlayerERK6Entity",      (void **)&old_isPlayer},
	   {"_ZNK3Mob12getMaxHealthEv",      (void **)&old_getMaxHealth},
		{"_ZNK16BaseAttributeMap11getInstanceERKSs",      (void **)&old_BaseAttributeMapgetInstance},
		{"_ZNK6Entity10getNameTagEv",      (void **)&old_EntitygetName},
	    {"_ZN12ItemInstance8_setItemEi",      (void **)&old_setItem}, //初始化一个物品item
	    {"_ZN9Inventory9clearSlotE",      (void **)&old_InventoryclearSlot}, //清除仓库物品
	    {"_ZN9Inventory3addER12ItemInstanceb",      (void **)&old_Inventory3add}, //仓库添加物品
	    {"_ZNK9LevelData11getGameTypeEv",      (void **)&old_getGameType},//获取游戏类型
	    {"_ZN9Minecraft11getGameModeEv",      (void **)&old_getGameMode},//获取游戏模式
	    {"_ZNK9LevelData7getSeedEv",		(void **)&old_getSeed},  //获取世界种子

};

void hook_symbols(soinfo * handle) {

#ifdef NDK_DEBUG
	LogD("<%s> %s %s handle = %x( funcs = %d)", __FUNCTION__, __DATE__,__TIME__,(int)handle, sizeof(gHookSymbols)/sizeof(gHookSymbols[0]));
#endif
	baseA=handle->base;
	for (int i = 0; i < sizeof(gFindSymbols) / sizeof(gFindSymbols[0]); i++) {
		FIND_SYMBOL find = gFindSymbols[i];
		*find.func = dlsym(handle, find.symbol);
#ifdef NDK_DEBUG
		LogD("<HookSymbol> symbol = 0x%x : %s", (int)*find.func, find.symbol);
#endif
	}

	for (int i = 0; i < sizeof(gHookSymbols) / sizeof(gHookSymbols[0]); i++) {
		HOOK_SYMBOL hook = gHookSymbols[i];
		inlineHookSymbol(handle, hook.symbol, hook.new_func, hook.old_func);

#ifdef NDK_DEBUG
		LogD("<HookSymbol> symbol = %s(%x), new = 0x%x, old = 0x%x", hook.symbol, (int)getAddress(handle,hook.symbol ),(int)hook.new_func, (int)*hook.old_func);
#endif
	}

}
