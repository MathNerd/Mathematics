
#include <octave/oct.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

#define CSTRING const char*
#define CONV_CHAR_DIGIT_TO_INT(c) ((c)-'0')

typedef enum Parse2DDoubleVectorReturnCodeEnum
{
    Parse2DDoubleVectorReturnCode_SUCCESS,
    Parse2DDoubleVectorReturnCode_ERROR__EXPECTS_OPENING_BRACKET,
    Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT,
    Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT,
    Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTERS_AT_LINE_END
} Parse2DDoubleVectorReturnCodeEnum;

static CSTRING Parse2DDoubleVectorString(Parse2DDoubleVectorReturnCodeEnum return_code)
{
    static CSTRING return_code_names[] = {
        "Parse2DDoubleVectorReturnCode_SUCCESS",
        "Parse2DDoubleVectorReturnCode_ERROR__EXPECTS_OPENING_BRACKET",
        "Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT",
        "Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT",
        "Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTERS_AT_LINE_END"
    };
    
    return return_code_names[return_code];
}

static Parse2DDoubleVectorReturnCodeEnum Parse2DDoubleVector(const std::string& str, double& x, double& y)
{
    typedef enum STATES { 
        STATE_START, // Starting state
        STATE_0, 
        STATE_1,
        STATE_2,
        STATE_3,
        STATE_4,
        STATE_5,
        STATE_6,
        STATE_7,
        STATE_8,
        STATE_9,
        STATE_10,
        STATE_11,
        STATE_12,
        STATE_FINISH // Finish state
    } STATES;
    
    STATES state = STATE_START;
    Parse2DDoubleVectorReturnCodeEnum return_code = Parse2DDoubleVectorReturnCode_SUCCESS;
    x = 0;
    y = 0;
    
    int sign = 1;
    double frac = 0;
    double expo = 1;
        
    for (size_t i = 0; state != STATE_FINISH && i < str.length(); i++)
    {
        char c = str[i];
        
        switch(state)
        {
            case STATE_START:
                if (c == '[')
                    state = STATE_0;
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__EXPECTS_OPENING_BRACKET;
                }
            break;
            
            case STATE_0:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_0;
                }
                else if (isdigit(c))
                {
                    state = STATE_2;
                    x = 10 * x + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '.')
                {
                    state = STATE_3;
                }
                else if (c == '+')
                {
                    state = STATE_1;
                }
                else if (c == '-')
                {
                    state = STATE_1;
                    sign = -1;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
                
            case STATE_1:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_1;    
                }
                else if (isdigit(c))
                {
                    state = STATE_2;
                    x = 10 * x + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '.')
                {
                    state = STATE_3;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
            
            case STATE_2:
                if (isdigit(c))
                {
                    // Do not change the state:
                    // state = STATE_2;
                    x = 10 * x + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '.')
                {
                    state = STATE_4;
                }
                else if (isspace(c))
                {
                    state = STATE_5;
                    x *= sign;
                    sign = 1;
                }
                else if (c == ',')
                {
                    state = STATE_6;
                    x *= sign;
                    sign = 1;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
            
            case STATE_3:
                if (isdigit(c))
                {
                    state = STATE_4;
                    expo /= 10.0;
                    frac += CONV_CHAR_DIGIT_TO_INT(c) * expo;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
            
            case STATE_4:
                if (isdigit(c))
                {
                    // Do not change the state:
                    // state = STATE_4;
                    expo /= 10.0;
                    frac += CONV_CHAR_DIGIT_TO_INT(c) * expo;
                }
                else if (isspace(c))
                {
                    state = STATE_5;
                    x += frac;
                    x *= sign;
                    sign = 1;
                    expo = 1.0;
                    frac = 0.0;
                }
                else if (c == ',')
                {
                    state = STATE_6;
                    x += frac;
                    x *= sign;
                    sign = 1;
                    expo = 1.0;
                    frac = 0.0;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
            
            case STATE_5:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_5;
                }
                else if (c == ',')
                {
                    state = STATE_6;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_FIRST_COMPONENT;
                }
            break;
            
            case STATE_6:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_6;
                }
                else if (isdigit(c))
                {
                    state = STATE_8;
                    y = 10 * y + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '+')
                {
                    state = STATE_7;
                }
                else if (c == '-')
                {
                    state = STATE_7;
                    sign = -1;
                }
                else if (c == '.')
                {
                    state = STATE_9;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }
            break;
            
            case STATE_7:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_7;
                }
                else if (isdigit(c))
                {
                    state = STATE_8;
                    y = 10 * y + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '.')
                {
                    state = STATE_9;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }
            break;
            
            case STATE_8:
                if (isdigit(c))
                {
                    // Do not change the state:
                    // state = STATE_8;
                    y = 10 * y + CONV_CHAR_DIGIT_TO_INT(c);
                }
                else if (c == '.')
                {
                    state = STATE_10;
                }
                else if (isspace(c))
                {
                    state = STATE_11;
                }
                else if (c == ']')
                {
                    state = STATE_12;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }  
            break;
            
            case STATE_9:
                if (isdigit(c))
                {
                    state = STATE_10;
                    expo /= 10.0;
                    frac += CONV_CHAR_DIGIT_TO_INT(c) * expo;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }
            break;
            
            case STATE_10:
                if (isdigit(c))
                {
                    // Do not change the state:
                    // state = STATE_10;
                    expo /= 10.0;
                    frac += CONV_CHAR_DIGIT_TO_INT(c) * expo;
                }
                else if (isspace(c))
                {
                    state = STATE_11;
                    y += frac;
                    y *= sign;
                }
                else if (c == ']')
                {
                    state = STATE_12;
                    y += frac;
                    y *= sign;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }
            break;
            
            case STATE_11:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_11;
                }
                else if (c == ']')
                {
                    state = STATE_12;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTER_WHILE_READING_SECOND_COMPONENT;
                }
            break;
            
            case STATE_12:
                if (isspace(c))
                {
                    // Do not change the state:
                    // state = STATE_12;
                }
                else
                {
                    state = STATE_FINISH;
                    return_code = Parse2DDoubleVectorReturnCode_ERROR__UNRECOGNIZED_CHARACTERS_AT_LINE_END;
                }
            break;
        }
    }
    
    return return_code;
}

DEFUN_DLD(scene_parser_IMP, args, nargout, "Reads a '.scene' file.")
{
    int nargin = args.length();
    
    if (nargin != 1)
        octave_stdout << "Expects exactly one parameter of string type that will hold the full path to the '.scene' file.\n";
    else
    {
        if (args(0).is_string())
        {
            std::string file_full_path = args(0).string_value();
            
            if (!error_state)
            {
                boost::property_tree::ptree pt;
                boost::property_tree::ini_parser::read_ini(file_full_path, pt);

                //------------------------------------------------------------------------------
                
                std::string str_point_0 = pt.get<std::string>("point_0");
                std::string str_point_velocity = pt.get<std::string>("point_velocity");
                std::string str_point_radius = pt.get<std::string>("point_radius");
                std::string str_point_drag_acceleration = pt.get<std::string>("point_drag_acceleration");
                
                std::string str_rectangle_bottom_left_corner = pt.get<std::string>("rectangle_bottom_left_corner");
                std::string str_rectangle_size = pt.get<std::string>("rectangle_size");
                std::string str_rectangle_velocity = pt.get<std::string>("rectangle_velocity");
                std::string str_rectangle_drag_acceleration = pt.get<std::string>("rectangle_drag_acceleration");
                
                //------------------------------------------------------------------------------
                
                dim_vector dv(1, 13);
                NDArray array(dv);
                
                double x, y;
                Parse2DDoubleVectorReturnCodeEnum return_code;
               
                return_code = Parse2DDoubleVector(str_point_0, x, y);
                if (return_code != Parse2DDoubleVectorReturnCode_SUCCESS)
                {
                    octave_stdout << "Error while parsing value of \'" << "point_0" << "\'.\n";
                    octave_stdout << "Error details: " << Parse2DDoubleVectorString(return_code) << "\n";
                }
                else
                {
                    array(0,0) = x;
                    array(0,1) = y;
                }
                
                return_code = Parse2DDoubleVector(str_point_velocity, x, y);
                if (return_code != Parse2DDoubleVectorReturnCode_SUCCESS)
                {
                    octave_stdout << "Error while parsing value of \'" << "point_velocity" << "\'.\n";
                    octave_stdout << "Error details: " << Parse2DDoubleVectorString(return_code) << "\n";
                }
                else
                {
                    array(0,2) = x;
                    array(0,3) = y;
                }
                
                array(0,4) = std::stod(str_point_radius);
                array(0,5) = std::stoi(str_point_drag_acceleration);
                
                //------------------------------------------------------------------------------
                
                return_code = Parse2DDoubleVector(str_rectangle_bottom_left_corner, x, y);
                if (return_code != Parse2DDoubleVectorReturnCode_SUCCESS)
                {
                    octave_stdout << "Error while parsing value of \'" << "rectangle_bottom_left_corner" << "\'.\n";
                    octave_stdout << "Error details: " << Parse2DDoubleVectorString(return_code) << "\n";
                }
                else
                {
                    array(0,6) = x;
                    array(0,7) = y;
                }
                
                return_code = Parse2DDoubleVector(str_rectangle_size, x, y);
                if (return_code != Parse2DDoubleVectorReturnCode_SUCCESS)
                {
                    octave_stdout << "Error while parsing value of \'" << "rectangle_size" << "\'.\n";
                    octave_stdout << "Error details: " << Parse2DDoubleVectorString(return_code) << "\n";
                }
                else
                {
                    array(0,8) = x;
                    array(0,9) = y;
                }
                
                return_code = Parse2DDoubleVector(str_rectangle_velocity, x, y);
                if (return_code != Parse2DDoubleVectorReturnCode_SUCCESS)
                {
                    octave_stdout << "Error while parsing value of \'" << "rectangle_velocity" << "\'.\n";
                    octave_stdout << "Error details: " << Parse2DDoubleVectorString(return_code) << "\n";
                }
                else
                {
                    array(0,10) = x;
                    array(0,11) = y;
                }
                
                array(0,12) = std::stoi(str_rectangle_drag_acceleration);
                
                return octave_value(array);
            }
            else
            {
                octave_stdout << "Octave error.\n";
            }
        }
        else
        {
            octave_stdout << "Expects a string argument.\n";
        }
    }
    
    return octave_value_list();
}