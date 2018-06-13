
from django.utils import translation

dicnames = [    
    ["Meaured DateTime","측정일시"],
    ["Equipment No","장비번호"],    
    ["Sensor No","센서번호"],    
    ["Received DateTime","수신일시"],    

    ["Department Name","부서명"],
    ["Department Sequence","부서코드"],    
    ["Department No","부서번호"],    
    ["Department Name","부서명"],  

    ["Employee Sequence","사원내부코드"],    
    ["Employee No","사원번호"],    
    ["Emplyee Name","사원명"],    

    ["Equipment Sequence","장비내부코드"],    
    ["Equipment Name","장비명"],    
    ["Equipment Type","장비종류"],        
    ["Use Department","사용부서"],  

    ["Service Request Sequence","정비요청내부코드"],    
    ["Service Request No","정비요청번호"],    
    ["Receipt Date","입고일"],        
    ["Use Department","사용부서"],      
    ["Request person","의뢰자"], 
    ["Receipt Employee","입고자"], 
    ["Find Date","발견일"], 
    ["Failure Location","고장부위"], 
    ["Warehouse Location","보관위치"], 

    ["Work start date","작업시작일"], 
    ["Work finished date","작업종료일"], 

    ["Failure Status","고장상태"], 
    ["Finder Action","발견자 조치"], 
    ["Repair Work","수리내역"], 

    ["Remark","비고"],  
    ["Faioure Protection plan","장애대응책"],  
    ["References","참고사항"],  
    ["Work Results","결과내용"],  
    ["Issue Date","출고일"],  
    ["Recipient","수령자"],      

    ["Remark","비고"],  
    ["Employee","사원"],  
    ["Department","부서"],  
    ["Equipment","장비"],     
    ["Maintenance Request","정비요청"],   
    ["Maintenance Results","정비결과"],       
]

def getName(langname):
    try:
        if translation.get_language().upper() != "EN-US":
            for dicname in dicnames:
                if dicname[0].upper() == langname.upper():
                    return dicname[1]
        return langname

    except:
        return langname
    
    