#include <iostream>

using namespace std;

int page_str[30], n_pages;
void fifo();
void lru();
void optimal();

int main()
{
    cout << "Enter the Number of Pages ==> ";
    cin >> n_pages;

    cout << "\nEnter " << n_pages << " pages in sequence  ==>  ";
    for (int i = 0; i < n_pages; i++)
        cin >> page_str[i];

    char ch;
    do
    {
        int choice;
        cout << "\n\n 1. Fifo Page Replacement ";
        cout << "  \n 2. LRU Page Replacement";
        cout << "  \n 3. Optimal Page Replacement";
        cout << "  \n 0. Exit";
        cout << "\n\n Enter choice  ==>  ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            fifo();
            break;
        case 2:
            lru();
            break;
        case 3:
            optimal();
            break;
        case 0:
            return 0;
            break;
        default:
            cout << "\nInvalid Choice" << endl;
        }

        cin.ignore();
        cout << "Do You want to continue ?... ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    return 0;
}

void fifo()
{
    int frame_size;
    cout << "\nEnter size of page frame :- ";
    cin >> frame_size;

    int page_frame[frame_size];
    for (int &i : page_frame)
        i = -1;

    cout << "\nPage String:-  \n";
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << page_str[i] << " ";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;

    cout << "\n\n************FIFO PAGE REPLACEMENT ALGO************" << endl;

    int cnt = 0, fault = 0;
    for (int i = 0; i < n_pages; i++)
    {
        int flag = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (page_str[i] == page_frame[j])
            {
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            page_frame[cnt] = page_str[i];
            cnt = (cnt + 1) % frame_size;
            fault++;
        }

        for (int i = 0; i < frame_size; i++)
            if (page_frame[i] != -1)
                cout << page_frame[i] << "  ";
        cout << endl;
    }

    cout << "\nTotal Faults occured:- " << fault << endl
         << endl;
}

void lru()
{
    int frame_size;
    cout << "\nEnter size of page frame :- ";
    cin >> frame_size;

    int page_frame[frame_size], page_pos[frame_size];
    for (int &i : page_frame)
        i = -1;

    for (int &i : page_pos)
        i = -1;

    // Optional
    cout << "\nPage String:-  \n";
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << page_str[i] << " ";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;

    // Algorithm starts Here
    cout << "\n\n************LRU PAGE REPLACEMENT ALGO:************" << endl;
    int fault = 0;
    for (int i = 0; i < n_pages; i++)
    {
        int flag = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (page_str[i] == page_frame[j])
            {
                flag = 1;
                page_pos[j] = i;
                break;
            }
        }

        if (flag == 0)
        {
            fault++;
            int pos = 0;

            for (int j = 0; j < frame_size; j++)
            {
                if (page_frame[j] == -1)
                {
                    page_pos[j] = i;
                    pos = j;
                    break;
                }
                if (page_pos[pos] > page_pos[j])
                {
                    pos = j;
                }
            }
            page_frame[pos] = page_str[i];
            page_pos[pos] = i;
        }

        for (int i = 0; i < frame_size; i++)
            if (page_frame[i] != -1)
                cout << page_frame[i] << "  ";
        cout << endl;
    }

    cout << "\nTotal Faults occured:- " << fault << endl
         << endl;
}

void optimal()
{
    int frame_size;
    cout << "\nEnter size of page frame :- ";
    cin >> frame_size;

    int page_frame[frame_size], page_pos[frame_size];
    for (int &i : page_frame)
        i = -1;

    // Optional
    cout << "\nPage String:-  \n";
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << page_str[i] << " ";
    cout << endl;
    for (int i = 0; i < n_pages; i++)
        cout << "--";
    cout << endl;

    // Algorithm starts Here
    cout << "\n\n************Optimal PAGE REPLACEMENT ALGO************" << endl;
    int fault = 0;
    for (int i = 0; i < n_pages; i++)
    {

        // Checking if the page is available in page frame
        int flag = 0;
        for (int j = 0; j < frame_size; j++)
        {
            if (page_str[i] == page_frame[j])
            {
                flag = 1;

                break;
            }
        }

        // If Page is not available then apply Optimal algorithm and print page frame
        if (flag == 0)
        {
            fault++;
            int pos = 0;

            for (int j = 0; j < frame_size; j++)
            {

                // If there is no data in frame then save the current page at that framme position
                if (page_frame[j] == -1)
                {
                    pos = j;
                    break;
                }

                // Get the next positon of the pages in frame and get the frame which is far
                bool found = 0;
                for (int k = i + 1; k < n_pages; k++)
                {
                    if (page_frame[j] == page_str[k])
                    {
                        found = 1;
                        page_pos[j] = k;
                        break;
                    }
                }

                if (!found)
                {
                    page_pos[j] = n_pages;
                }

                if (page_pos[pos] < page_pos[j])
                {
                    pos = j;
                }
            }
            page_frame[pos] = page_str[i];
        }

        // If Page is available then just print data in current page frame

        for (int i = 0; i < frame_size; i++)
            if (page_frame[i] != -1)
                cout << page_frame[i] << "  ";
        cout << endl;
    }

    cout << "\nTotal Faults occured:- " << fault << endl
         << endl;
}
