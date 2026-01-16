def split_file_by_lines(input_file, lines_per_file=6):
    with open(input_file, 'r') as infile:
        lines = infile.readlines()
    
    total_lines = len(lines)
    num_files = (total_lines + lines_per_file - 1) // lines_per_file  # Ceiling division
    
    for i in range(num_files):
        start = i * lines_per_file
        end = start + lines_per_file
        chunk_lines = lines[start:end]
        
        output_filename = f"output_part_{i + 1}.txt"
        with open(output_filename, 'w') as outfile:
            outfile.writelines(chunk_lines)
        print(f"Wrote {len(chunk_lines)} lines to {output_filename}")

# Example usage
split_file_by_lines("filelist394175.txt", lines_per_file=6)

