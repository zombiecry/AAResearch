#ifndef SCSINGLETON_H
#define SCSINGLETON_H
namespace sc{
#define DECLARE_SINGLETON(className)				\
	public:											\
		static className *GetInstance();			\
	private:										\
		static className *ms_instance;

#define DEFINE_SINGLETON(className)					\
	className *className::ms_instance=NULL;			\
	className *className::GetInstance(){			\
		if (!ms_instance){							\
			ms_instance=new className();			\
		}											\
		return ms_instance;							\
	}


	
#define DEFINE_TEMPLATE1_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE1_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define DEFINE_TEMPLATE2_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE2_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define DEFINE_TEMPLATE3_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE3_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define DEFINE_TEMPLATE4_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE4_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define DEFINE_TEMPLATE5_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE5_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))
#define DEFINE_TEMPLATE6_SINGLETON(className,...)					\
	DEFINE_TEMPLATE_SINGLETON_(className,TEMPLATE6_CLASS_DECLARE(__VA_ARGS__),TEMPLATE_PARAM(__VA_ARGS__))



#define DECLARE_TEMPLATE_SINGLETON(className,...)												\
public:																							\
	static className<__VA_ARGS__> *GetInstance();												\
private:																						\
	static className<__VA_ARGS__> *ms_instance;



#define TEMPLATE1_CLASS_DECLARE(t)	\
	class t
#define TEMPLATE2_CLASS_DECLARE(t1,t2)	\
	TEMPLATE1_CLASS_DECLARE(t1),class t2

#define TEMPLATE3_CLASS_DECLARE(t1,t2,t3)	\
	TEMPLATE2_CLASS_DECLARE(t1,t2),class t3

#define TEMPLATE4_CLASS_DECLARE(t1,t2,t3,t4)	\
	TEMPLATE3_CLASS_DECLARE(t1,t2,t3),class t4

#define TEMPLATE5_CLASS_DECLARE(t1,t2,t3,t4,t5)	\
	TEMPLATE4_CLASS_DECLARE(t1,t2,t3,t4),class t5

#define TEMPLATE6_CLASS_DECLARE(t1,t2,t3,t4,t5,t6)	\
	TEMPLATE5_CLASS_DECLARE(t1,t2,t3,t4,t5),class t6


#define TEMPLATE_PARAM(...)			\
	__VA_ARGS__


#define DEFINE_TEMPLATE_SINGLETON_(className,templateClassDeclare,templateParam)								\
	template <templateClassDeclare> className<templateParam> *className<templateParam>::ms_instance=NULL;		\
	template <templateClassDeclare> className<templateParam> *className<templateParam>::GetInstance(){			\
		if (!ms_instance){																						\
			ms_instance=new className<templateParam>();															\
		}																										\
	    return ms_instance;																						\
    }


}



#endif