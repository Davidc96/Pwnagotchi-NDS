#include "pwngotchi.h"

Pwngotchi::Pwngotchi()
{
    m_apcontroller = new APController();
    m_spicontroller = new SPIController();
    m_uicontroller = new UIController();

    m_currentChannel = 0;
    m_totalAPs = 0;
    m_happyness = 100;
    m_grade = 20;
    m_APTargetsCount = 0;

    m_isWorking = false;
    m_isAttacking = false;
    m_isEvaluating = false;
    m_isObtaining = false;
    m_askTotalAP = true;
}

Pwngotchi::~Pwngotchi()
{

}

void Pwngotchi::init()
{
    m_uicontroller->init();
    m_spicontroller->init();
    m_wificontroller->connectAP();
}

void Pwngotchi::setDebugFrame(int frame)
{
    m_dbg_frame = frame;
}

void Pwngotchi::doWorkCallback()
{
    //u8 response[255];
    //iprintf("Flags A: %d E: %d O: %d DN: %d\n", m_isAttacking, m_isEvaluating, m_isObtaining, m_isWorking);
    if(!m_isWorking)
    {
        m_isWorking = true;
        
        int what_he_wants = calculateWhatHeWants();
        #ifdef DEBUG
            iprintf("Option choosed to work: %d\n", what_he_wants);
        #endif
        // 3 factores        
        switch(what_he_wants)
        {
            case PWNGOTCHI_ATTACK:
                m_isAttacking = true;
                break;
            case PWNGOTCHI_EVALUATE:
                m_isEvaluating = true;
                break;
            case PWNGOTCHI_OBTAIN:
                m_isObtaining = true;
                break;
            case PWNGOTCHI_DONOTHING:
                m_isWorking = false;
                break;
        }
        
    }
    else
    {
        if(m_isAttacking)
        {
            if(m_selectedTarget != NULL)
            {
                char response[255];
                m_wificontroller->sendCommand((char *)WIFI_ATTACK, response);

                // Attacking is always fun :-)
                changeHappyness(10);

                // Remove the selected Target and reduce the value at 50 %
                m_selectedTarget->setAttacked(true);
                m_selectedTarget = NULL;
                m_APTargetsCount = 0;
            }

            m_isAttacking = false;

        }
        else if(m_isObtaining)
        {            
            GiveAPResponse apstr;
            char response[255];
            m_wificontroller->sendCommand((char *)WIFI_GIVEMEAP, response);

            // Let's split the response
            char * ptr = strtok(response, ";");
            apstr.ssid = ptr;
            ptr = strtok(NULL, ";");
            apstr.connected_clients = atoi(ptr);
            ptr = strtok(NULL, ";");
            apstr.signal_strength = atoi(ptr);

            //sscanf(response, "%s;%d;%d", apstr.ssid, &apstr.connected_clients, &apstr.signal_strength);
            
            #ifdef DEBUG
                iprintf("\nSSID: %s CC: %d S: %d", apstr.ssid, apstr.connected_clients, apstr.signal_strength);
            #endif

            APNode * apnode = m_apcontroller->getNodeBySSID(apstr.ssid);
            if(apnode == NULL)
            {
                m_apcontroller->createNode(apstr.ssid, apstr.connected_clients, apstr.signal_strength, 0);
            }
            else
            {   
                // Update values
                apnode->getAP()->setConnectedClients(apstr.connected_clients);
                apnode->getAP()->setSignalStrength(apstr.signal_strength);

                // Because is a repeated one pwngotchi loses it's motivation
                changeHappyness(-20);
            }

            m_wificontroller->sendCommand((char *)WIFI_NEXTAP, response);

            // Works makes u unhappy
            changeHappyness(-10);
            m_isObtaining = false;
        }
        else if(m_isEvaluating)
        {
            APNode * first_element = m_apcontroller->getFirstElement()->getNode(); // Actually the real element (first element is in blank)
            
            if(first_element != NULL)
            {
                APNode * iterator = first_element;
                int sum_values = 0;
                int targets_attacked = 0;
                // Reset targeteable APs
                m_APTargetsCount = 0;

                while(iterator != NULL)
                {   
                    int signal = iterator->getAP()->getSignalStrength();  // Puntuaction from 0 (bad signal) to 100 (very good signal)
                    int clients = iterator->getAP()->getConnectedClients(); // Puntuaction from 0 (no people) to 100 (that's a lot of people)
                    
                    int old_value = iterator->getValue();

                    // Target with good signal, good clients (Always actitude is important)
                    int new_value = signal * 0.4 + clients * 0.3 + m_happyness * 0.2 + old_value * 0.1;
                    if(iterator->isAttacked())
                    {
                        new_value = new_value / 2; // Let's reduce the value if this AP was attacked
                        targets_attacked++; // Let's count all the attacked targets
                    }

                    sum_values += new_value;
                    
                    #ifdef DEBUG
                        iprintf("Nota: %d\n", new_value);
                    #endif
                    
                    iterator->setValue(new_value);

                    if(new_value >= m_grade && !iterator->isAttacked())
                    {
                        // Our pwngotchi finds a target, let's increase it's happyness
                        changeHappyness(10);

                        // Check if the selected target is worst than the new
                        if(m_selectedTarget != NULL)
                        {
                            if(new_value > m_selectedTarget->getValue())
                            {
                                m_selectedTarget = iterator;
                            }
                        }
                        else
                        {
                            m_selectedTarget = iterator;
                        }

                        // Set the target to the AP
                        char response[255];
                        m_wificontroller->sendCommand((char *)WIFI_SELECTAP, response);

                        // Add possible targeteable AP to the counter
                        m_APTargetsCount++;
                    }
                    else
                    {
                        // Our pwngotchi starts to loose its fate
                        changeHappyness(-10);
                    }

                    // Let's increase or reduce the spectations
                    //m_grade = (m_grade + new_value) / 2;
                    

                    iterator = iterator->getNode();
                }
                
                // Let's increase or reduce the spectations
                m_grade = (m_grade + (sum_values / m_apcontroller->getNumElements())) / 2;

                // All targets are attacked Pwngotchi is bored
                if(targets_attacked == m_totalAPs)
                {
                    m_happyness = 20; // Let's super reduce the Pwngotchi happyness and make it being bored
                    m_totalAPs = 0;
                    m_grade = 70;
                    m_apcontroller->flush();
                }
                
                #ifdef DEBUG
                    iprintf("APTargets: %d\n", m_APTargetsCount);
                #endif
            }

            m_isEvaluating = false;

        }

        m_isWorking = false;
    }
}

void Pwngotchi::changeHappyness(int rate)
{
    int temp_value = m_happyness + rate;
    if(temp_value > 100)
    {
        temp_value = 100;
    }

    if(temp_value < 0)
    {
        temp_value = 0;
    }

    m_happyness = temp_value;
}

void Pwngotchi::run()
{
    
    char * sentence = (char *)"";
    
    #ifdef DEBUG
        iprintf("\x1b[2J");
    #endif
    
    int resp = 1;
    //int resp = m_wificontroller->connectAP();
    //iprintf(resp);
    if(resp != 1)
    {
        m_status = INTENSE;
        sentence = (char *)ESP_NOT_FOUND_MESSAGE;
    }
    else
    {   
        // TODO: Future: Add DOG image into subscreen
        
        if(m_happyness >= 80)
        {
            // Check if we want the total of APs around
            if(m_askTotalAP)
            {   
                char response[255];
                m_wificontroller->sendCommand((char *)WIFI_GETAPCOUNT, response);
                m_totalAPs = atoi(response);

                #ifdef DEBUG
                    iprintf("APS obtained %s. Total: %d\n", response, m_totalAPs);
                #endif
                m_askTotalAP = false;
                m_askRescanAP = true; // Let's set the variable to true just in case
            }
            
            m_status = HAPPY;
        }

        if(m_happyness <= 50)
        {
            m_status = AWAKED;
        }

        int wants_to_work = m_happyness * 0.8 + getRandomNumber() * 0.2;

        #ifdef DEBUG
            iprintf("Pwngotchi happyness: %d\n", m_happyness);
            iprintf("Pwngotchi wants to work: %d\n", wants_to_work);
            iprintf("Number of wifis: %d\n", m_apcontroller->getNumElements());
            iprintf("Total APs given: %d\n", m_totalAPs);
            iprintf("Grade to work: %d\n\n", m_grade);
        #endif
        
        if(wants_to_work >= 70)
        {
            m_status = LEFT_LOOKING;
            
            // Check if there are APs
            if(m_totalAPs > 0)
            {
                doWorkCallback();
            }
            else
            {
                m_askTotalAP = true;
            }
        }
        
        if(m_isWorking)
        {
            if(m_isAttacking)
            {
                m_status = COOL;
                sprintf(sentence, DEAUTH_MESSAGE, m_selectedTarget->getAP()->getSSID());
                //sentence = (char *)DEAUTH_MESSAGE;

            }
            else
            {
                sentence = (char * )WORKING_MESSAGE;
                if(getRandomNumber() % 2 == 0)
                {
                    m_status = LEFT_LOOKING;
                }
                else
                {
                    m_status = RIGHT_LOOKING;
                }
            }
        }
        else
        {
            m_status = HAPPY;
            sentence = (char *)DONOTHING_MESSAGE;
        }

        if(wants_to_work < 70 && m_status == AWAKED)
        {
            
            // All the APs are evaluated and attacked, let's rescan de environment
            if(m_askRescanAP)
            {
                char response[255];
                m_wificontroller->sendCommand((char *)WIFI_RESCAN, response);
                m_askRescanAP = false;
                m_askTotalAP = true;
            }

            sentence = (char *)BORED_MESSAGE;
        }
        else if(wants_to_work < 70 && m_status == HAPPY)
        {
            if(getRandomNumber() % 2 == 0)
            {
                m_status = LEFT_HAPPY;
            }
            else
            {
                m_status = RIGHT_HAPPY;
            }

            sentence = (char *)APNOTFOUND_MESSAGE;
            // Let's motivated a little bit
        }

        

    }

    m_uicontroller->setFace(m_status);
    m_uicontroller->setSentence(sentence);
    m_uicontroller->setAPTotal(m_totalAPs);
    m_uicontroller->setCurrentChannel(m_currentChannel);
    m_uicontroller->setAPinChannel(m_apcontroller->getNumElements());
    m_uicontroller->setDbgFrame(m_dbg_frame);
    if(m_selectedTarget != NULL)
    {
        m_uicontroller->setSSIDName(m_selectedTarget->getAP()->getSSID());
    }
    else
    {
        m_uicontroller->setSSIDName((char*)"None");
    }

    m_uicontroller->update();
    changeHappyness(5);
    delay(2);
}

int Pwngotchi::calculateWhatHeWants()
{
    //int prob_box[30];

    int attack_value = 0;
    int obtain_value = 0;
    int evaluate_value = 0;

    if(m_selectedTarget == NULL)
    {
        if(m_apcontroller->getNumElements() == 0)
        {
            attack_value = 0;
            obtain_value = 30;
            evaluate_value = 0;
        }
        else
        {
            attack_value = 0;
            obtain_value = map(m_totalAPs - m_apcontroller->getNumElements(), 0, m_totalAPs, 0, 10); // Takes into consideration the number of APs registered
            evaluate_value = map(m_apcontroller->getNumElements() - m_APTargetsCount, 0, m_totalAPs, 0, 10); // Takes into consideration the number of elements - the total targeteable AP
        }
    }
    else
    {
        attack_value = map(m_APTargetsCount, 0, m_totalAPs, 0, 10); // Takes into consideration the targeteable count
        obtain_value = map(m_totalAPs - m_apcontroller->getNumElements(), 0, m_totalAPs, 0, 10); // Takes into consideration the number of APs registered
        evaluate_value = 0; // Takes into consideration the number of elements - the total targeteable AP
    }

    int prob_box_size = attack_value + obtain_value + evaluate_value;

    #ifdef DEBUG
        iprintf("\n\nWork AV: %d OV: %d EV: %d\n", attack_value, obtain_value, evaluate_value);
    #endif
    int prob_box[prob_box_size];

    // Add attack values first 
    for(int i = 0; i < attack_value; i++)
    {
        prob_box[i] = PWNGOTCHI_ATTACK;
    }

    // Add obtain values into prob_box
    for(int i = attack_value; i < (attack_value + obtain_value); i++)
    {
        prob_box[i] = PWNGOTCHI_OBTAIN;
    }

    // Add evaluate values
    for(int i = (attack_value + obtain_value); i < (attack_value + obtain_value + evaluate_value); i++)
    {
        prob_box[i] = PWNGOTCHI_EVALUATE;
    }

    // Lets throw the DICE 10 times
    int option = 0;
    for(int i = 0; i < 10; i++)
    {
        option = random() % (attack_value + obtain_value + evaluate_value);
    }

    #ifdef DEBUG
        iprintf("Option: %d\n", option);
    #endif
    
    return prob_box[option];
    
}