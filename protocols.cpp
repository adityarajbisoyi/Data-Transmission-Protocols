#include <iostream>
using namespace std;
int Frame_Size = 20;
// stop and wait ARQ
void StopAndWait(int arr[])
{
    int recieved_frame;
    int i = 0;

    while (i < Frame_Size)
    {
        int transmitted_frame = arr[i];
        cout << "Enter the Frame Recieved: ";
        cin >> recieved_frame;
        if (recieved_frame == transmitted_frame)
        {
            cout << "Acknowledgement Recieved!" << endl
                 << "Transmitting next frame " << endl;
            i++;
        }
        else
        {
            cout << "Frame Damaged or not recieved! " << endl
                 << "Intializing Retransmission! " << endl;
        }
        if (i == Frame_Size)
        {
            cout << "All Frames Transferred Successfully! " << endl;
        }
        cout << endl;
    }
}
// Go back N ARQ
void GoBackN(int arr[], int window_size)
{
    int window[window_size];
    int i = 0;
    while (i < Frame_Size)
    {
        cout << "Current Window [";
        for (int j = i, cnt = 0; cnt < window_size; j++, cnt++)
        {
            window[cnt] = arr[j];
            cout << window[cnt] << ", ";
        }
        cout << "\b\b]" << endl;

        int transmitted_frame = window[0];
        int recieved_frame;
        cout << "Enter the frame recieved: ";
        cin >> recieved_frame;

        if (recieved_frame != transmitted_frame)
        {
            cout << "Acknowledgement not recieved Retransmtting the entire window" << endl
                 << "[ ";
            for (int cnt = 0; cnt < window_size; cnt++)
            {
                cout << window[cnt] << ", ";
            }
            cout << "\b\b ]" << endl
                 << endl;
        }
        else
        {
            cout << "Transmission Succesfull, Window Slides --> " << endl;
            i++;
        }
    }
}
// Selective repeat request ARQ
void Selective_repeat_req(int arr[], int window_size)
{
    int transmitter_window[window_size];
    int reciever_buffer[window_size];
    int i = 0;
    while (i < Frame_Size)
    {
        cout << "Enter the frames : ";
        for (int j = 0; j < window_size; j++)
        {
            transmitter_window[j] = arr[i];
            i++;
            cin >> reciever_buffer[j];
        }

        // sorting mechanism in reciever side
        for (int j = 0; j < window_size; j++)
        {
            for (int k = 0; k < window_size - j - 1; k++)
            {
                if (reciever_buffer[k] > reciever_buffer[k + 1])
                {
                    int temp = reciever_buffer[k + 1];
                    reciever_buffer[k + 1] = reciever_buffer[k];
                    reciever_buffer[k] = temp;
                }
            }
        }

        for (int j = 0; j < window_size; j++)
            cout << "Frame Recieved: " << reciever_buffer[j] << endl;
        int error_frames[] = {0, 0, 0, 0, 0};
        bool Success;
        for (int k = 0, itr = 0; k < window_size; k++)
        {
            int temp_frame = transmitter_window[k];
            bool found = false;
            for (int j = 0; j < window_size; j++)
            {
                if (temp_frame == reciever_buffer[j])
                {
                    found = true;
                }
            }
            found == true ? Success = true : error_frames[itr++] = temp_frame;
        }
        if (error_frames[0] != 0)
            Success = false;

        if (Success == false)
        {
            for (int itr = 0; error_frames[itr] != 0; itr++)
            {
                cout << "Re-Transmitting Frame: " << error_frames[itr] << endl;
            }
        }
        cout << "Frames Transmitted \n[";
        for (int cnt = 0; cnt < window_size; cnt++)
        {
            cout << transmitter_window[cnt] << ", ";
        }
        cout << "\b\b ]" << endl
             << endl;
    }
}
int main()
{
    // Intializing the frames
    int frames[25];
    for (int i = 0; i < 25; i++)
    {
        if (i < 20)
        {
            frames[i] = i + 1;
        }
        else
        {
            frames[i] = 0;
        }
    }

    // Stop and wait
    // StopAndWait(frames);

    // Go back and N mechanism
    // GoBackN(frames, 5);

    Selective_repeat_req(frames, 5);
}